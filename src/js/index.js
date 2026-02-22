/**
 * Main entry point for Node.js bindings.
 * Exposes the C++ addon and JavaScript wrappers.
 */
const claudeSkills = require('./build/Release/claude_skills.node');
const path = require('path');

class SkillManager {
    constructor(skillsPath) {
        this.skillsPath = skillsPath || path.join(__dirname, '../skills');
    }

    listSkills() {
        return claudeSkills.listSkills(this.skillsPath);
    }

    executeSkill(skillName, params) {
        return claudeSkills.executeSkill(skillName, params);
    }
}

module.exports = {
    SkillManager,
    fileUtils: {
        readFile: claudeSkills.readFile,
        listFiles: claudeSkills.listFiles
    }
};