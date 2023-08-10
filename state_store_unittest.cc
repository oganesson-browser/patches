// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "extensions/browser/state_store.h"

// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



#include "extensions/browser/warning_service.h"

#include "content/public/test/test_browser_context.h"
#include "extensions/browser/extensions_test.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

#include "components/value_store/test_value_store_factory.h"
#include "components/value_store/testing_value_store.h"


namespace extensions {

namespace {

const char kExpensionId[] = "test_extension_id";
const char kKey[] = "test_key";
const char kValue[] = "value";

using StateStoreTest = ExtensionsTest;

}  // namespace

// Check that after setting a value, we get the same value out
TEST_F(StateStoreTest, SetAndGetValue) {
  content::TestBrowserContext browser_context;
  value_store::TestValueStoreFactory* store_factory = new value_store::TestValueStoreFactory();
  StateStore* state_store = new StateStore(&browser_context, store_factory, StateStore::BackendType::STATE, false);

  state_store->SetExtensionValue(kExpensionId, kKey, base::Value(kValue));
  state_store->GetExtensionValue(kExpensionId, kKey, base::BindOnce([](absl::optional<base::Value> value) {
    ASSERT_TRUE(value.has_value());
    ASSERT_EQ(*value, kValue);
  }));
}

// Check that after inserting a key, we get the same value out
TEST_F(StateStoreTest, ValueClearedOnUninstall) {
  content::TestBrowserContext browser_context;

  value_store::TestValueStoreFactory* store_factory = new value_store::TestValueStoreFactory();
  StateStore* state_store = new StateStore(&browser_context, store_factory, StateStore::BackendType::STATE, false);

  base::Value::Dict manifest;
  manifest.Set("manifest_version", 3);
  std::string error;
  scoped_refptr<extensions::Extension> extension = extensions::Extension::Create(
    base::FilePath(),
    extensions::mojom::ManifestLocation::kInternal,
    manifest,
    0,
    kExpensionId,
    &error);
  extensions::Extension* extension_ = extension.get();
  ExtensionRegistry* extension_registry = ExtensionRegistry::Get(&browser_context);

  state_store->RegisterKey(kKey);

  state_store->SetExtensionValue(kExpensionId, kKey, base::Value(kValue));

  extension_registry->TriggerOnUninstalled(extension_, extensions::UninstallReason::UNINSTALL_REASON_FOR_TESTING);

  state_store->GetExtensionValue(kExpensionId, kKey, base::BindOnce([](absl::optional<base::Value> value) {
    ASSERT_TRUE(value.has_value());
    ASSERT_EQ(*value, kValue);
  }));
}

  // store->RegisterUpdatePersistentKey(kUpdatePersistentKey);

/*
TestExtensionSystem::TestExtensionSystem(Profile* profile)
    : profile_(profile),
      store_factory_(new value_store::TestValueStoreFactory()),
      state_store_(new StateStore(profile_,
                                  store_factory_,
                                  StateStore::BackendType::RULES,
                                  false)),
      quota_service_(new QuotaService()),
      app_sorting_(new ChromeAppSorting(profile_)) {
#if BUILDFLAG(IS_CHROMEOS_ASH)
  if (!user_manager::UserManager::IsInitialized()) {
    scoped_user_manager_ = std::make_unique<user_manager::ScopedUserManager>(
        std::make_unique<user_manager::FakeUserManager>());
  }
#endif
}




  TestWarningService warning_service(&browser_context);
  MockObserver observer;
  warning_service.AddObserver(&observer);

  ExtensionIdSet affected_extensions;
  affected_extensions.insert(ext1_id);
  // Insert warning for the first time.
  EXPECT_CALL(observer, ExtensionWarningsChanged(affected_extensions));
  warning_service.AddWarning(
      Warning::CreateNetworkDelayWarning(ext1_id));
  testing::Mock::VerifyAndClearExpectations(&warning_service);

  // Second insertion of same warning does not trigger anything.
  warning_service.AddWarning(Warning::CreateNetworkDelayWarning(ext1_id));
  testing::Mock::VerifyAndClearExpectations(&warning_service);

  warning_service.RemoveObserver(&observer);
}

// Check that ClearWarnings deletes exactly the specified warnings and
// triggers notifications where appropriate.
TEST_F(WarningServiceTest, ClearWarnings) {
  content::TestBrowserContext browser_context;
  TestWarningService warning_service(&browser_context);
  MockObserver observer;
  warning_service.AddObserver(&observer);

  // Insert two unique warnings in one batch.
  std::set<std::string> affected_extensions;
  affected_extensions.insert(ext1_id);
  affected_extensions.insert(ext2_id);
  EXPECT_CALL(observer, ExtensionWarningsChanged(affected_extensions));
  WarningSet warning_set;
  warning_set.insert(Warning::CreateNetworkDelayWarning(ext1_id));
  warning_set.insert(Warning::CreateRepeatedCacheFlushesWarning(ext2_id));
  warning_service.AddWarnings(warning_set);
  testing::Mock::VerifyAndClearExpectations(&warning_service);

  // Remove one warning and check that the badge remains.
  affected_extensions.clear();
  affected_extensions.insert(ext2_id);
  EXPECT_CALL(observer, ExtensionWarningsChanged(affected_extensions));
  std::set<Warning::WarningType> to_clear;
  to_clear.insert(warning_2);
  warning_service.ClearWarnings(to_clear);
  testing::Mock::VerifyAndClearExpectations(&warning_service);

  // Check that the correct warnings appear in |warnings|.
  std::set<Warning::WarningType> existing_warnings =
      warning_service.GetWarningTypesAffectingExtension(ext1_id);
  EXPECT_EQ(1u, existing_warnings.size());
  existing_warnings =
      warning_service.GetWarningTypesAffectingExtension(ext2_id);
  EXPECT_EQ(0u, existing_warnings.size());

  // Remove the other one warning.
  affected_extensions.clear();
  affected_extensions.insert(ext1_id);
  EXPECT_CALL(observer, ExtensionWarningsChanged(affected_extensions));
  to_clear.insert(warning_1);
  warning_service.ClearWarnings(to_clear);
  testing::Mock::VerifyAndClearExpectations(&warning_service);

  // Check that no warnings remain.
  existing_warnings =
      warning_service.GetWarningTypesAffectingExtension(ext1_id);
  EXPECT_EQ(0u, existing_warnings.size());
  existing_warnings =
      warning_service.GetWarningTypesAffectingExtension(ext2_id);
  EXPECT_EQ(0u, existing_warnings.size());

  warning_service.RemoveObserver(&observer);
}
*/

}  // namespace extensions
