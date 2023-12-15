#!/usr/bin/env python3

import os
import shutil
import re

ROOT_PATH = os.getcwd()

paths = ['include/mif/linear/vector3', 'src/linear/vector3']

dimensions = [2, 4]


def replace_file_contents(dim, file, outfile):
    f = open(file)
    contents = f.read()
    f.close()
    output = contents
    output = re.sub(r'Vector3', lambda x: f'Vector{dim}', output)
    output = re.sub(r'vector3', lambda x: f'vector{dim}', output)

    if dim == 4:
        output = re.sub(re.escape('VEC31(V)(VEC3(V, V, V))'), lambda x: 'VEC41(V)(VEC4(V, V, V, V))', output)
        output = re.sub(re.escape('VEC3(X, Y, Z)'), lambda x: 'VEC4(X, Y, Z, W)', output)
        output = re.sub(
            re.escape(
                '.x = (a).x op (b).x, .y = (a).y op (b).y, .z = (a).z op (b).z'),
            lambda x: '.x = (a).x op (b).x, .y = (a).y op (b).y, .z = (a).z op (b).z, .w = (a).w op (b).w', output)
        output = re.sub(
            re.escape(
                '.x = (a).x op (b), .y = (a).y op (b), .z = (a).z op (b)'),
            lambda x: '.x = (a).x op (b), .y = (a).y op (b), .z = (a).z op (b), .w = (a).w op (b)', output)

        output = re.sub(re.escape('(v).x, (v).y, (v).z'), lambda x: '(v).x, (v).y, (v).z, (v).w', output)
        output = re.sub(re.escape('"VEC3(%"#P", %"#P", %"#P")'), lambda x: '"VEC4(%"#P", %"#P", %"#P", %"#P")', output)
        output = re.sub(re.escape('VEC3(%12.6f, %12.6f, %12.6f)'), lambda x: 'VEC4(%12.6f, %12.6f, %12.6f, %12.6f)', output)
        output = re.sub(re.escape('{ .x = (X), .y = (Y), .z = (Z) }'), lambda x: '{ .x = (X), .y = (Y), .z = (Z), .w = (W) }', output)
        output = re.sub(re.escape('a.x + b.x, a.y + b.y, a.z + b.z'), lambda x: 'a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w', output)
        output = re.sub(re.escape('a.x - b.x, a.y - b.y, a.z - b.z'), lambda x: 'a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w', output)
        output = re.sub(re.escape('a.x * b.x, a.y * b.y, a.z * b.z'), lambda x: 'a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w', output)
        output = re.sub(re.escape('a.x * s, a.y * s, a.z * s'), lambda x: 'a.x * s, a.y * s, a.z * s, a.w * s', output)
        output = re.sub(r'(([a-z]).z / \w+)+(\))', lambda x: x.group(1) + f', {x.group(2)}.w / mag' + x.group(3), output)
        output = re.sub(r'(1.0f / ([a-z])\.z)+(\))', lambda x: x.group(1) + f', 1.0f / {x.group(2)}.w' + x.group(3), output)
        output = re.sub(re.escape('(x, y, z)'), lambda x: '(x, y, z, w)', output)
        output = re.sub(re.escape('func(a.z)'), lambda x: 'func(a.z), func(a.w)', output)
        output = re.sub(r'(?:float z = (\w+)\((\w+)\.z, (\w+)\.z, (\w+)\.z\);+)+', lambda x: f'{x.group(0)}\n  float w = {x.group(1)}({x.group(2)}.w, {x.group(3)}.w, {x.group(4)}.w);', output)
        output = re.sub(r'float z = (\w+)\((\w+)\.z, (\w+)\.z, (\w+)\);', lambda x: f'{x.group(0)}\n  float w = {x.group(1)}({x.group(2)}.w, {x.group(3)}.w, {x.group(4)});', output)
        output = re.sub(r'float z = (\w+)\((\w+)\.z, (\w+), (\w+)\);', lambda x: f'{x.group(0)}\n  float w = {x.group(1)}({x.group(2)}.w, {x.group(3)}, {x.group(4)});', output)
        output = re.sub(re.escape('VEC3(0.0f, 0.0f, 0.0f)'), lambda x: 'VEC4(0.0f, 0.0f, 0.0f, 0.0f)', output)

    output = re.sub(r"VEC3", lambda x: f"VEC{dim}", output)
    output = re.sub(r"v3", lambda x: 'v4', output)

    f = open(outfile, 'w+')
    f.write(output)
    f.close()
    print(f'Wrote {outfile}')


def generate_vector_headers(dim, basepath):
    out_dir = basepath.replace('vector3', f'vector{dim}')
    input_dir = os.path.join(ROOT_PATH, basepath)
    os.makedirs(out_dir, exist_ok=True)
    #shutil.copytree(input_dir, out_dir, dirs_exist_ok=True)


    for root, dirs, files in os.walk(input_dir):
        for file in files:
            if file.endswith('.c') or file.endswith('.h'):
                print(file)
                replace_file_contents(dim, os.path.join(basepath, file), os.path.join(out_dir, str(file).replace('vector3', f'vector{dim}')))
 

def run():
    for dim in dimensions:
        for basepath in paths:
            generate_vector_headers(dim, basepath)


run()
