import { promisify } from 'node:util';
import { exec } from 'node:child_process';
const execP = promisify(exec);

export async function gitClone(remoteURL, localPath)  {
    const { stdout, stderr } = await execP(`git clone ${remoteURL} ${localPath || ''}`);
    console.error('git clone', remoteURL, localPath);
}

export async function gitApply(srcDir, patchPath) {
  const { stdout, stderr } = await execP(`git apply ${patchPath}`, {cwd: srcDir});
  console.error('git apply', srcDir, patchPath, stdout, stderr);
}
