#!/usr/bin/env python3
"""
Generate AWS architecture from requirements.
"""
import json
import yaml
import argparse
from pathlib import Path

def generate_serverless(requirements):
    """Generate a simple serverless template."""
    return {
        "AWSTemplateFormatVersion": "2010-09-09",
        "Resources": {
            "MyFunction": {
                "Type": "AWS::Lambda::Function",
                "Properties": {
                    "Runtime": "python3.9",
                    "Handler": "index.handler",
                    "Code": {
                        "ZipFile": "def handler(event, context):\n    return 'Hello from Lambda'"
                    }
                }
            }
        }
    }

def generate_vpc(requirements):
    """Generate a VPC template."""
    return {
        "Resources": {
            "VPC": {
                "Type": "AWS::EC2::VPC",
                "Properties": {
                    "CidrBlock": "10.0.0.0/16"
                }
            }
        }
    }

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--requirements', help='JSON file with requirements')
    parser.add_argument('--output', default='yaml', choices=['yaml', 'json'])
    args = parser.parse_args()

    if args.requirements:
        with open(args.requirements) as f:
            req = json.load(f)
    else:
        req = {"type": "serverless", "name": "demo"}

    if req.get('type') == 'vpc':
        result = generate_vpc(req)
    else:
        result = generate_serverless(req)

    if args.output == 'yaml':
        print(yaml.dump(result, default_flow_style=False))
    else:
        print(json.dumps(result, indent=2))

if __name__ == '__main__':
    main()