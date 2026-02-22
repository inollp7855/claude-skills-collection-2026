#!/usr/bin/env python3
"""
Prompt Factory Skill – generates high-quality prompts for various roles.
"""
import os
import json
import argparse
from pathlib import Path
import random

class PromptFactory:
    def __init__(self, templates_path=None):
        self.templates_path = templates_path or Path(__file__).parent / "../../skills/prompt-factory/templates"
        
    def generate_prompt(self, role, context=""):
        """Generate a prompt for a given role."""
        templates = {
            "senior-dev": "You are a senior software engineer with 10+ years of experience...",
            "product-manager": "Act as a product manager at a fast-growing startup...",
        }
        if role in templates:
            base = templates[role]
        else:
            base = f"You are a {role}."
        
        if context:
            return f"{base}\nContext: {context}\nNow, please..."
        else:
            return base
    
    def list_roles(self):
        return ["senior-dev", "product-manager", "data-scientist", "devops-engineer"]

def main():
    parser = argparse.ArgumentParser(description="Prompt Factory Skill")
    parser.add_argument("--role", required=True, help="Target role")
    parser.add_argument("--context", help="Additional context")
    args = parser.parse_args()
    
    factory = PromptFactory()
    prompt = factory.generate_prompt(args.role, args.context)
    print(prompt)

if __name__ == "__main__":
    main()