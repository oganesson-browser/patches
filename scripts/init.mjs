
// TODO
import info from './upstream.json' assert { type: 'json' };
import { gitClone } from './git.mjs';

import { dirname, join } from 'node:path';
import { fileURLToPath } from 'node:url';

const __dirname = dirname(fileURLToPath(import.meta.url));
const upstreamDirname = join(__dirname, '../upstream');

async function getCloneDestination({repo, dest}) {
    const dest_ = join(__dirname, '../upstream', dest);
    await gitClone(repo, dest_);
}

await getCloneDestination(info.depotTools);
//await gitClone(chromium.repo, chromium.dest);
