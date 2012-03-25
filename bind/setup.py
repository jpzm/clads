# Copyright (C) 2012 Joao Paulo de Souza Medeiros
#
# Author: Joao Paulo de Souza Medeiros <jpsm1985@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA


from distutils.core import setup, Extension


list_module = Extension('list',
                        include_dirs = ['../'],
                        extra_objects = ['../code/list.o',
                                         '../code/clads.o'],
                        extra_compile_args = ['-Wall', '-ggdb'],
                        sources = ['list.c'])

graph_module = Extension('graph',
                         include_dirs = ['../'],
                         extra_objects = ['../code/graph.o',
                                          '../code/clads.o'],
                         extra_compile_args = ['-Wall', '-ggdb'],
                         sources = ['graph.c'])


setup(name = 'clads',
      version = '0.1',
      author='Joao Medeiros',
      author_email='jpsm1985@gmail.com',
      description = 'This is the CLADS package',
      ext_modules = [list_module, graph_module])
