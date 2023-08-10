
# List changed files

git diff --name-only

# Get changed built files

gn refs out/Small/ --testonly=true --type=executable --all <file>


# Too hard to remove

components/metrics


# Test failures

out/Small/unit_tests --gtest_filter="TestChromeColorsService*"
