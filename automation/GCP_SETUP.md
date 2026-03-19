# ES2 Agent Pipeline — GCP Setup Guide

## Overview

This guide covers how to run the ES2 automation pipeline on a GCP VM using Claude Code CLI in headless mode.

---

## 1. Create GCP VM

```bash
# Create an e2-medium instance (2 vCPU, 4GB RAM is sufficient)
gcloud compute instances create es2-agent \
    --zone=asia-east1-b \
    --machine-type=e2-medium \
    --image-family=ubuntu-2404-lts-amd64 \
    --image-project=ubuntu-os-cloud \
    --boot-disk-size=20GB \
    --tags=es2-agent

# SSH into the instance
gcloud compute ssh es2-agent --zone=asia-east1-b
```

---

## 2. Install Dependencies

```bash
# Update system
sudo apt update && sudo apt upgrade -y

# Install Node.js 20+ (required for Claude Code CLI)
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
sudo apt install -y nodejs

# Verify
node --version   # Should be v20+
npm --version

# Install git
sudo apt install -y git
```

---

## 3. Install Claude Code CLI

```bash
npm install -g @anthropic-ai/claude-code
```

Verify installation:

```bash
claude --version
```

---

## 4. Configure Authentication

Set your Anthropic API key:

```bash
# Option A: Export in current session
export ANTHROPIC_API_KEY="sk-ant-api03-..."

# Option B: Add to ~/.bashrc for persistence
echo 'export ANTHROPIC_API_KEY="sk-ant-api03-..."' >> ~/.bashrc
source ~/.bashrc

# Option C: Use GCP Secret Manager (recommended for production)
gcloud secrets create anthropic-api-key \
    --replication-policy="automatic"
echo -n "sk-ant-api03-..." | \
    gcloud secrets versions add anthropic-api-key --data-file=-

# Then in your script:
export ANTHROPIC_API_KEY=$(gcloud secrets versions access latest \
    --secret="anthropic-api-key")
```

---

## 5. Clone Repository

```bash
cd ~
git clone https://github.com/Transformer666/es2_mudlib.git
cd es2_mudlib
```

Configure git identity (for commits):

```bash
git config user.name "ES2 Agent"
git config user.email "agent@es2.muds.net"
```

---

## 6. Run the Pipeline

### Run All Tasks

```bash
cd ~/es2_mudlib
bash automation/run_pipeline.sh
```

### Run a Single Task

```bash
# Run only task 01 (analyze missing content)
bash automation/run_pipeline.sh 1

# Run only task 03 (implement rooms)
bash automation/run_pipeline.sh 3
```

### Run Manually with Claude Code

```bash
# Run a single task file directly
claude -p "$(cat automation/01_analyze_missing.md)" \
    --allowedTools "Read,Write,Edit,Glob,Grep,Bash,WebFetch" \
    --max-turns 30

# Run with restricted permissions (read-only analysis)
claude -p "$(cat automation/01_analyze_missing.md)" \
    --allowedTools "Read,Glob,Grep,WebFetch" \
    --max-turns 20

# Run with JSON output for logging
claude -p "$(cat automation/03_implement_rooms.md)" \
    --allowedTools "Read,Write,Edit,Glob,Grep,Bash" \
    --max-turns 50 \
    --output-format json > docs/task03_result.json
```

### Run Static Validation Tests

```bash
bash automation/run_tests.sh          # Run all tests
bash automation/run_tests.sh rooms    # Test rooms only
bash automation/run_tests.sh npcs     # Test NPCs only
bash automation/run_tests.sh daemons  # Test daemons only
bash automation/run_tests.sh exits    # Test bidirectional exits only
```

---

## 7. Key Claude Code CLI Flags

| Flag | Description | Example |
|------|-------------|---------|
| `-p` | Headless/print mode (non-interactive) | `claude -p "task"` |
| `--allowedTools` | Auto-approve tools without prompting | `"Read,Write,Edit,Bash"` |
| `--disallowedTools` | Deny specific tools | `"Bash(rm *),Bash(sudo *)"` |
| `--max-turns` | Limit agent iterations | `--max-turns 30` |
| `--output-format` | Output format: text/json/stream-json | `--output-format json` |
| `--model` | Override model | `--model claude-sonnet-4-5-20250929` |
| `--append-system-prompt` | Add extra instructions | `"Only modify files under d/"` |

### Recommended Tool Permissions for Pipeline

```bash
# Full development (create/edit files + run commands)
--allowedTools "Read,Write,Edit,Glob,Grep,Bash"

# Read-only analysis
--allowedTools "Read,Glob,Grep"

# Development without network access
--allowedTools "Read,Write,Edit,Glob,Grep,Bash" \
--disallowedTools "WebFetch,Bash(curl *),Bash(wget *)"

# Safe mode (no destructive commands)
--allowedTools "Read,Write,Edit,Glob,Grep,Bash(ls *),Bash(git status *),Bash(git diff *)" \
--disallowedTools "Bash(rm *),Bash(sudo *),Bash(git push *)"
```

---

## 8. Cost Optimization

### Model Selection

| Model | Cost (input/output per MTok) | Use Case |
|-------|-----|----------|
| Claude Opus 4.6 | $5 / $25 | Complex architecture, multi-file changes |
| Claude Sonnet 4.5 | $3 / $15 | General development (recommended default) |
| Claude Haiku 4.5 | $1 / $5 | Simple tasks, validation, analysis |

### Use Sonnet for Most Tasks

```bash
# Override model to Sonnet (cheaper, still capable)
claude -p "$(cat automation/03_implement_rooms.md)" \
    --model claude-sonnet-4-5-20250929 \
    --allowedTools "Read,Write,Edit,Glob,Grep,Bash" \
    --max-turns 30
```

### Limit Max Turns

```bash
# Prevent runaway iterations
--max-turns 20   # For simple tasks
--max-turns 50   # For complex multi-file tasks
```

### Estimated Pipeline Cost

| Task | Estimated Turns | Sonnet Cost | Opus Cost |
|------|----------------|-------------|-----------|
| 01 Analyze | 10-15 | ~$0.50 | ~$2.50 |
| 02 Races | 15-25 | ~$1.00 | ~$5.00 |
| 03 Rooms | 20-40 | ~$2.00 | ~$10.00 |
| 04 NPCs | 20-40 | ~$2.00 | ~$10.00 |
| 05 Equipment | 10-20 | ~$0.50 | ~$2.50 |
| **Total** | | **~$6** | **~$30** |

*Estimates are rough and vary based on task complexity and codebase size.*

---

## 9. Update Pipeline Script for GCP

The `run_pipeline.sh` uses `claude -p` which works in headless mode. To add recommended flags, edit the `run_task()` function:

```bash
run_task() {
    local task_file="$1"
    local task_desc="$2"
    local task_path="$TASK_DIR/$task_file"

    if [ ! -f "$task_path" ]; then
        warn "Task file not found, skip: $task_path"
        return 0
    fi

    log "Running task: $task_desc"

    if claude -p "$(cat $task_path)" \
        --allowedTools "Read,Write,Edit,Glob,Grep,Bash" \
        --disallowedTools "Bash(rm -rf *),Bash(sudo *),Bash(git push *)" \
        --max-turns 40 \
        --model claude-sonnet-4-5-20250929 \
        2>&1 | tee -a $LOG_FILE; then
        success "Task done: $task_desc"
    else
        error "Task failed: $task_desc"
        exit 1
    fi
}
```

---

## 10. Cron / Scheduled Runs (Optional)

To run the pipeline on a schedule:

```bash
# Edit crontab
crontab -e

# Run pipeline every Sunday at 2 AM
0 2 * * 0 cd ~/es2_mudlib && ANTHROPIC_API_KEY="sk-ant-..." bash automation/run_pipeline.sh >> /var/log/es2-pipeline.log 2>&1
```

Or use a systemd timer for better logging:

```bash
# /etc/systemd/system/es2-pipeline.timer
[Unit]
Description=ES2 Agent Pipeline Timer

[Timer]
OnCalendar=Sun *-*-* 02:00:00
Persistent=true

[Install]
WantedBy=timers.target
```

```bash
# /etc/systemd/system/es2-pipeline.service
[Unit]
Description=ES2 Agent Pipeline

[Service]
Type=oneshot
User=your_username
WorkingDirectory=/home/your_username/es2_mudlib
Environment="ANTHROPIC_API_KEY=sk-ant-..."
ExecStart=/bin/bash automation/run_pipeline.sh
StandardOutput=append:/var/log/es2-pipeline.log
StandardError=append:/var/log/es2-pipeline.log
```

```bash
sudo systemctl enable es2-pipeline.timer
sudo systemctl start es2-pipeline.timer
```

---

## 11. Monitoring

### Check Pipeline Logs

```bash
# View pipeline log
cat docs/pipeline_run.log

# View test report
cat docs/test_report.md

# Watch pipeline in real-time
tail -f docs/pipeline_run.log
```

### Check API Usage

Monitor your API usage at: https://console.anthropic.com/settings/usage

---

## Quick Start Summary

```bash
# 1. SSH into GCP VM
gcloud compute ssh es2-agent --zone=asia-east1-b

# 2. One-time setup
sudo apt update && sudo apt install -y nodejs npm git
npm install -g @anthropic-ai/claude-code
export ANTHROPIC_API_KEY="sk-ant-..."
git clone https://github.com/Transformer666/es2_mudlib.git
cd es2_mudlib

# 3. Run pipeline
bash automation/run_pipeline.sh

# 4. Run tests
bash automation/run_tests.sh

# 5. Review results
cat docs/test_report.md
cat docs/pipeline_run.log
```
