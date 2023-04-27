#! /usr/bin/python3 
#A simply python script to quickly create a project directory for my C Library.
#The general directory structure is as such:
# <Project Name>
# |
# src/
#   <Project Name>.c
#   <Project Name>.h
# test/
#   <Project Name>.c
# README.md
# Makefile
#
#The makefile will already be prefilled with the necessary arguments to get the
#program up and running

import os
import argparse


def Main():
    parser = argparse.ArgumentParser()
    parser.add_argument("proj_name", help="Enter project name.")
    parser.add_argument("proj_dir", nargs='?', default=os.getcwd(), help="Enter project directory.")
    
    args = parser.parse_args()
    
    if(os.path.exists(args.proj_dir + '/' + args.proj_name + '/')):
        print("Path already exists. Quitting program.")
        exit(1)
        
    proj_name = args.proj_name
    proj_dir = args.proj_dir
    
    print("Creating folders...")
    create_dir(proj_name, proj_dir)
    
    print("Creating files...")
    create_files(proj_name, proj_dir)

    print("Project successfully started at " + proj_dir + "/" + proj_name + "/")
    

#Three folders are created, project/, project/src/, and project/test
def create_dir(proj_name, proj_dir):
    path = proj_dir + '/' + proj_name + '/'
    os.makedirs(path + '/' + "src/")
    os.makedirs(path + '/' + "test/")

#five files are created, project.c/.h, projectTest.c, Makefile, and readme.md
def create_files(proj_name, proj_dir):
    path = proj_dir + '/' + proj_name + '/' 
    
    open(path + "src/" + proj_name + '.c', 'a').close()
    open(path + "src/" + proj_name + '.h', 'a').close()
    open(path + "test/" + proj_name + 'Test.c', 'a').close()
    
    #Open the template makefile, replace with the appropriate project name,
    #We will keep the makefile in a res/ folder.
    if not os.path.exists(os.getcwd() + '/' + "res/templateMakefile"):
        print(path + "res/templateMakefile")
        print("Missing templateMakefile error")
        exit(1)
        
    template_file = open(os.getcwd() + '/' + 'res/templateMakefile', 'r')
    new_makefile_data = template_file.read().replace('%', proj_name)
    new_makefile = open(path + "Makefile", 'w')
    new_makefile.write(new_makefile_data)
    
    template_file.close()
    new_makefile.close()

    open(path + "README.md", 'a').close()
    return

if __name__ == '__main__':
    Main()