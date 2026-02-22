#!/usr/bin/env python3
"""
Generate prompts using the Prompt Factory skill.
"""
import argparse
import sys
sys.path.append('../../../src/python/skill_wrappers')
from prompt_factory import PromptFactory

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--role', required=True)
    parser.add_argument('--context')
    args = parser.parse_args()

    factory = PromptFactory()
    prompt = factory.generate_prompt(args.role, args.context)
    print(prompt)

if __name__ == '__main__':
    main()