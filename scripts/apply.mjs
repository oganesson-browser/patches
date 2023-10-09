import { argv } from 'node:process';
import { readdir, readFile, rm } from 'node:fs/promises';
import { join } from 'node:path';

import { gitApply } from './git.mjs';

const patchesLocation = '../data/';
const srcLocation = '../../src/';

function getParams() {
  const [, , arg1, arg2] = argv;

  const patches = arg1 || (new URL(patchesLocation, import.meta.url)).pathname;
  const src = arg2 || (new URL(srcLocation, import.meta.url)).pathname;
  return {patches, src};
}


async function removeDir(path) {
  console.log('rm here', path);
  // TODO: enable me;
  return;
  await rm(path ,{ recursive: true, force: true });
}

async function applyStep(src, base, {type, path}) {
  switch(type) {
    case 'git apply':
      const loc = join(base, path);
      await gitApply(src, loc);
      break;
    case 'rm -rf':
      await removeDir(path);
      break;
  }
  console.error(type, path);
}

async function applyOne(src, path) {
  try {
    const infoPath = join(path, 'info.json');
    const infoStr = await readFile(infoPath, {encoding: 'utf-8'});
    const info_ = JSON.parse(infoStr);
    if (info_.skip) {
       return;
    }

    let info = info_;
    if (!Array.isArray(info_)) {
        info = info_.data;
    }
    for (const step of info) {
      await applyStep(src, path, step);
    }
  } catch(error) {
    console.error(error);
  }
}

async function apply({patches, src}) {
  try {
    const entries = await readdir(patches, {withFileTypes: true});
    for (const entry of entries) {
      if (!entry.isDirectory()) {
        continue;
      }
      const info = join(entry.path, entry.name);
      await applyOne(src, info);
    }
  } catch (err) {
    console.error(err);
  }
}

const params = getParams();
apply(params);
