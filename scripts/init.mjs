
import { mkdir, readFile } from 'node:fs/promises';
import { gitClone, execP } from './git.mjs';

import { dirname, join } from 'node:path';
import { fileURLToPath } from 'node:url';

const __dirname = dirname(fileURLToPath(import.meta.url));

const upstreamDirname = join(__dirname, '../upstream');

const info = JSON.parse(await readFile(join(__dirname, './upstream.json')));

async function cloneDestination({repo, dest}) {
    const dest_ = join(__dirname, '../upstream', dest);
    //OK
    //await gitClone(repo, dest_);
    return dest_;
}

async function run(command, dir) {
    await execP(command, {
        cwd: upstreamDirname,
        env: {
            PATH: `${dir}:${process.env.PATH}`,
        }
    });
}

async function depotToolsFetch(dir, nohooks = true, nohistory = true) {
    await run(`fetch ${nohooks && '--nohooks' || ''} ${nohistory && '--nohistory' || ''} chromium`, dir);
}

async function installDeps(dir) {
    await run('./build/install-build-deps.sh', dir);
}

async function gn(dir) {
    await run('gn gen out/Default', dir);
}

// OK
//await mkdir(upstreamDirname, { recursive: true });


const dest = await cloneDestination(info.depotTools);
//const envPath = `${dest}:${process.env.PATH}`;

//OK
//await depotToolsFetch(dest);

//OK
//await installDeps()

await gn();

//await gitClone(chromium.repo, chromium.dest);
