# Copyright (C) 2012 Joao Paulo de Souza Medeiros
#
# Author(s): Joao Paulo de Souza Medeiros <ignotus21@gmail.com>
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

"""
"""


import clads_list


class List(object):
    """
    """
    def __init__(self, cobj=None):
        """
        """
        if cobj == None:
            self.__cobj = clads_list.initialize()
        else:
            self.__cobj = clads_list.initialize(cobj)

        self.set_compare_callback(self.__bind_compare_callback)

    def __len__(self):
        """
        """
        return clads_list.size(self.__cobj)

    def __iter__(self):
        """
        """
        return self

    def next(self):
        """
        """
        n = clads_list.next(self.__cobj)

        if n is None:
            raise StopIteration

        return n

    def get_cobj(self):
        """
        """
        return self.__cobj

    def insert(self, value):
        """
        """
        return clads_list.insert(self.__cobj, value)

    def remove(self, value):
        """
        """
        return clads_list.remove(self.__cobj, value, 'F')

    def removeall(self, value):
        """
        """
        return clads_list.remove(self.__cobj, value, 'T')

    def set_compare_callback(self, f_compare):
        """
        """
        clads_list.set_compare_callback(self.__cobj, f_compare)

    @staticmethod
    def __bind_compare_callback(a, b):
        """
        """
        if (a < b):
            return -1
        if (a == b):
            return 0
        if (a > b):
            return 1
        return 2


if __name__ == "__main__":
    """
    """
    # testing with integer values
    print "[do] Number testing..."

    ln = List()

    print "insert:"

    ln.insert(4)
    ln.insert(2)
    ln.insert(2)
    ln.insert(3)
    ln.insert(4)

    for i in ln: print i, type(i)

    print "size", len(ln)

    print "remove 4:"

    ln.remove(4)

    for i in ln: print i

    print "insert 4:"

    ln.insert(4)

    for i in ln: print i

    print "removeall 4:"

    ln.removeall(4)

    for i in ln: print i

    print "removeall 3:"

    ln.removeall(3)

    for i in ln: print i

    print "removeall 2:"

    ln.removeall(2)

    for i in ln: print i

    print "size", len(ln)

    print "[done]"

    # testing with string values
    print "[do] String testing..."

    ls = List()

    print "insert:"

    ls.insert("john")
    ls.insert("mary")
    ls.insert("luca")
    ls.insert("john")
    ls.insert("lucy")

    for i in ls: print i, type(i)

    print "size", len(ls)

    print "remove `john':"

    ls.remove("john")

    for i in ls: print i

    print "insert `john':"

    ls.insert("john")

    for i in ls: print i

    print "removeall `john':"

    ls.removeall("john")

    for i in ls: print i

    print "removeall `lucy':"

    ls.removeall("lucy")

    for i in ls: print i

    print "removeall `luca':"

    ls.removeall("luca")

    for i in ls: print i

    print "remove `mary':"

    ls.remove("mary")

    for i in ls: print i

    print "size", len(ls)

    print "[done]"
