
import { mkdir, readFile } from 'node:fs/promises';
import { gitClone, execP } from './git.mjs';

import { dirname, join } from 'node:path';
import { fileURLToPath } from 'node:url';

const info = JSON.parse(await readFile('./upstream.json'));

const __dirname = dirname(fileURLToPath(import.meta.url));
const upstreamDirname = join(__dirname, '../upstream');

async function cloneDestination({repo, dest}) {
    const dest_ = join(__dirname, '../upstream', dest);
    //OK
    //await gitClone(repo, dest_);
    return dest_;
}

async function depotToolsFetch(dir, nohooks = true, nohistory = true) {
    await execP(`fetch ${nohooks && '--nohooks' || ''} ${nohistory && '--nohistory' || ''} chromium`, {
        cwd: upstreamDirname,
        env: {
            PATH: `${dir}:${process.env.PATH}`,
        }
    });
}

// OK
//await mkdir(upstreamDirname, { recursive: true });


const dest = await cloneDestination(info.depotTools);
//const envPath = `${dest}:${process.env.PATH}`;

await depotToolsFetch(dest);

//await gitClone(chromium.repo, chromium.dest);
