# S3 Site Helper Scripts

Minimal shell helpers for syncing static sites to and from Amazon S3 using the AWS CLI.
Designed to be **explicit, auditable, and hard to misuse**.

No config files. No magic. What you see is what runs.

---

## Files

* `s3-pull.sh` — Sync an S3 bucket **down** into the current local directory
* `s3-push.sh` — Sync the current local directory **up** to an S3 bucket (add/update/delete)
* `s3-rm.sh` — Remove a file or directory from an S3 bucket

---

## Requirements

* AWS CLI installed
* AWS credentials configured (`aws configure`)
* Commands must be run **from inside the site directory**

---

## Usage

### Pull a site from S3

```bash
s3-pull.sh <bucket-name> [region]
```

Example:

```bash
s3-pull.sh my-site-bucket us-east-2
```

Downloads the full bucket contents into the current directory.

---

### Push a site to S3

```bash
s3-push.sh <bucket-name> [region]
```

This will:

* Upload new and modified files
* Delete files in S3 that no longer exist locally
* Exclude `.git/` and `node_modules/`

Example:

```bash
s3-push.sh my-site-bucket us-east-2
```

⚠️ This is a **destructive sync**. Your local directory is treated as the source of truth.

---

### Remove a file or directory from S3

```bash
s3-rm.sh <bucket-name> <path> [region]
```

Examples:

```bash
s3-rm.sh my-site-bucket old-page.html
s3-rm.sh my-site-bucket assets/old/
```

---

## Safety Notes

* `s3-push.sh` refuses to run from a `_helpers` directory
* The directory you run the script from is **exactly** what gets deployed
* Always verify your location before pushing:

```bash
pwd
```

These helpers intentionally avoid hidden configuration so behavior remains obvious, predictable, and auditable.

---

## License

Use freely. Modify as needed.
Provided as-is, without warranty.

