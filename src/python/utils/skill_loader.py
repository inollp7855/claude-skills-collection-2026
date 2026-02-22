"""
Utility to load and manage Claude Skills from directories.
"""
import os
import yaml
from pathlib import Path

class SkillLoader:
    def __init__(self, skills_root):
        self.skills_root = Path(skills_root)
    
    def list_skills(self):
        skills = []
        for item in self.skills_root.iterdir():
            if item.is_dir() and (item / "SKILL.md").exists():
                skills.append(item.name)
        return skills
    
    def load_skill_config(self, skill_name):
        skill_path = self.skills_root / skill_name / "SKILL.md"
        if not skill_path.exists():
            return None
        with open(skill_path, 'r', encoding='utf-8') as f:
            content = f.read()
            if content.startswith('---'):
                parts = content.split('---', 2)
                if len(parts) >= 3:
                    try:
                        return yaml.safe_load(parts[1])
                    except:
                        return None
        return None