/**
 * Simple MCP (Model Context Protocol) server for Claude Skills.
 * Listens for requests and dispatches to the appropriate skill.
 */
const http = require('http');
const url = require('url');
const { SkillManager } = require('./index');

const PORT = 8080;
const skillManager = new SkillManager();

const server = http.createServer(async (req, res) => {
    const parsedUrl = url.parse(req.url, true);
    const pathname = parsedUrl.pathname;

    if (pathname === '/skills' && req.method === 'GET') {
        // List all skills
        const skills = skillManager.listSkills();
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ skills }));
    } else if (pathname.startsWith('/skills/') && req.method === 'POST') {
        // Execute a skill
        const skillName = pathname.split('/')[2];
        let body = '';
        req.on('data', chunk => body += chunk);
        req.on('end', () => {
            try {
                const params = JSON.parse(body);
                const result = skillManager.executeSkill(skillName, params);
                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ result }));
            } catch (e) {
                res.writeHead(400, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ error: e.message }));
            }
        });
    } else {
        res.writeHead(404);
        res.end();
    }
});

server.listen(PORT, () => {
    console.log(`MCP Server running on port ${PORT}`);
});