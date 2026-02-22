#!/usr/bin/env python3
"""
Wrapper to run the code reviewer from command line.
"""
import sys
import os
import json
import argparse
sys.path.append(os.path.join(os.path.dirname(__file__), '../../../src/python/skill_wrappers'))
from code_reviewer import CodeReviewer

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--file', help='File to review')
    parser.add_argument('--dir', help='Directory to review')
    parser.add_argument('--rules', help='Comma-separated rules')
    parser.add_argument('--format', default='text', choices=['text', 'json'])
    args = parser.parse_args()

    reviewer = CodeReviewer()
    if args.file:
        rules = args.rules.split(',') if args.rules else None
        result = reviewer.review_file(args.file, rules=rules)
    elif args.dir:
        result = {"error": "Directory review not implemented in demo"}
    else:
        parser.print_help()
        return

    if args.format == 'json':
        print(json.dumps(result, indent=2))
    else:
        if 'issues' in result:
            for issue in result['issues']:
                print(f"{issue['severity']}: {issue['message']}")

if __name__ == '__main__':
    main()