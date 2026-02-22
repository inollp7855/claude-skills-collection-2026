#!/usr/bin/env python3
"""
Generate a weekly report from template.
"""
import argparse
from pathlib import Path
import shutil
import datetime

def generate_report(template_path, output_path, data):
    with open(template_path, 'rb') as src:
        with open(output_path, 'wb') as dst:
            dst.write(src.read())
    with open(output_path, 'ab') as f:
        f.write(f"\n\nGenerated on {datetime.date.today()}".encode())

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--template', default='../templates/report.docx')
    parser.add_argument('--output', default='report.docx')
    args = parser.parse_args()

    generate_report(args.template, args.output, {})
    print(f"Report generated: {args.output}")

if __name__ == '__main__':
    main()