#!/usr/bin/env node
/**
 * Formats code review output into various formats.
 */
const fs = require('fs');

function formatText(report) {
    let output = `Found ${report.issues.length} issues\n\n`;
    report.issues.forEach(issue => {
        output += `[${issue.severity.toUpperCase()}] ${issue.file}:${issue.line}\n`;
        output += `  ${issue.message}\n`;
        if (issue.suggestion) output += `  Suggestion: ${issue.suggestion}\n\n`;
    });
    return output;
}

function formatMarkdown(report) {
    let md = `# Code Review Report\n\n`;
    md += `- **Files analyzed:** ${report.summary.files}\n`;
    md += `- **Total issues:** ${report.summary.issues}\n\n`;
    md += `| File | Line | Severity | Message |\n`;
    md += `|------|------|----------|---------|\n`;
    report.issues.forEach(issue => {
        md += `| ${issue.file} | ${issue.line} | ${issue.severity} | ${issue.message} |\n`;
    });
    return md;
}

if (require.main === module) {
    const input = fs.readFileSync(0, 'utf-8');
    try {
        const report = JSON.parse(input);
        const format = process.argv[2] || 'text';
        if (format === 'markdown') {
            console.log(formatMarkdown(report));
        } else {
            console.log(formatText(report));
        }
    } catch (e) {
        console.error('Invalid input JSON');
        process.exit(1);
    }
}

module.exports = { formatText, formatMarkdown };