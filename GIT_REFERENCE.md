# Git Reference - Common Workflows

Personal cheat sheet for Git workflows I use regularly.

---

## Workflow A: Start with a NEW empty repo on GitHub, then clone it locally

Use this when: You're starting fresh and want GitHub to be the "source of truth" from day one.

### Steps

1. **On GitHub.com:**
   - Click "New repository"
   - Give it a name (e.g., `my-project`)
   - Choose Public or Private
   - Check "Add a README file" (creates initial commit)
   - Optional: select .gitignore template, License
   - Click "Create repository"

2. **Copy the SSH clone URL** from the repo page:
   `git@github.com:Sanket-S-Shahane/my-project.git`

3. **Clone to your laptop:**
cd E:\Sanket_code_backups\GitHub
git clone git@github.com:Sanket-S-Shahane/my-project.git
cd my-project

4. **Verify:**
dir
git status
git log --oneline
   You should see the README file and one initial commit.

5. **Make changes, commit, push:**
edit files in VS Code
git status
git add filename
git status
git commit -m "describe what changed"
git push



---

## Workflow B: Start with an EXISTING local folder, push to a NEW GitHub repo

Use this when: You already have a project on your laptop with files in it, and you want to put it on GitHub for the first time.

### Steps

1. **On GitHub.com:**
   - Click "New repository"
   - Give it a name
   - Public or Private
   - **DO NOT** check "Add a README" (we want it empty)
   - **DO NOT** add .gitignore or License here (we'll add locally)
   - Click "Create repository"

2. **GitHub shows you setup instructions.** Copy the SSH URL from those instructions.

3. **In PowerShell, go to your existing local folder:**

cd E:\path\to\your\existing\folder

4. **Initialize Git in the folder:**
git init
git branch -M main
   This creates a hidden `.git` folder and sets the branch name to `main`.

5. **Stage all existing files for the first commit:**
git status
git add .
git status
   `git add .` adds everything in the folder (use a `.gitignore` first if needed).

6. **First commit:**
git commit -m "Initial commit"

7. **Connect local repo to the GitHub repo:**
git remote add origin git@github.com:Sanket-S-Shahane/my-project.git
   This tells your local repo where the GitHub copy lives.

8. **Push for the first time:**
git push -u origin main
   The `-u origin main` tells Git "remember this as the default upstream — next time just `git push` works."

9. **Verify on GitHub:** Refresh the repo page in your browser. Your files should appear.

---

## Daily workflow (after either A or B is set up)

This is the day-to-day cycle for any existing repo:
git status                    # see what changed


edit files in VS Code
git status                    # confirm what's modified
git diff filename             # see exact line changes (optional)
git add filename              # stage the file
git status                    # confirm it's staged
git commit -m "message"       # commit to local repo
git push                      # send to GitHub

---

## Reference: the most-used commands

| Command | Purpose |
|---|---|
| `git status` | What's changed, what's staged, what's pushed |
| `git add filename` | Stage a specific file |
| `git add .` | Stage everything in current folder |
| `git commit -m "message"` | Snapshot staged changes to local repo |
| `git push` | Upload local commits to GitHub |
| `git pull` | Download GitHub's commits to local |
| `git clone <url>` | Copy a remote repo to local |
| `git log --oneline` | Show commit history (compact) |
| `git diff filename` | Show line-by-line changes in a file |
| `git restore filename` | Discard unstaged changes |
| `git restore --staged filename` | Unstage a file (keep changes) |
| `git reset --soft HEAD~1` | Undo last commit, keep changes staged |
| `git reset --hard HEAD~1` | Undo last commit, throw away changes (dangerous) |
| `git revert <hash>` | Make a new commit that undoes an old one |
| `git reflog` | Show history of HEAD positions (recovery safety net) |



### Repository already exists on GitHub

Error:

```text
! [rejected] main -> main (fetch first)
error: failed to push some refs
```

Cause:
The GitHub repository already contains commits (README, LICENSE, .gitignore, etc.).

Fix:

```bash
git pull origin main --allow-unrelated-histories
git push -u origin main
```

Alternative (overwrite GitHub repository):

```bash
git push -u origin main --force
```

WARNING: `--force` replaces the contents of the remote repository.



### Check which GitHub repository is connected

```bash
git remote -v
```

Example output:

```text
origin  https://github.com/USERNAME/REPOSITORY.git (fetch)
origin  https://github.com/USERNAME/REPOSITORY.git (push)
```


### View commit history

Compact view:

```bash
git log --oneline
```

Detailed view:

```bash
git log
```
