#!/usr/bin/env python

from jinja2 import Environment, PackageLoader
env = Environment(loader=PackageLoader('testapp', 'templates'))
