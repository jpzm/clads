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

import list
import clads_list
import clads_graph


class Node(object):
    """
    """
    def __init__(self, cobj):
        """
        """
        self.__cobj = cobj

    def get_cobj(self):
        """
        """
        return self.__cobj

    def get_info(self):
        """
        """
        return clads_graph.get_node_info(self.__cobj)

    def get_id(self):
        """
        """
        return clads_graph.get_node_id(self.__cobj)

    def get_clustering(self):
        """
        """
        return clads_graph.get_node_clustering(self.__cobj)

    def get_degree(self):
        """
        """
        return clads_graph.get_node_degree(self.__cobj)


class Edge(object):
    """
    """
    def __init__(self, cobj):
        """
        """
        self.__cobj = cobj

    def get_cobj(self):
        """
        """
        return self.__cobj

    def get_info(self):
        """
        """
        return clads_graph.get_edge_info(self.__cobj)

    def get_id(self):
        """
        """
        return clads_graph.get_edge_id(self.__cobj)

    def get_nodes(self):
        """
        """
        return clads_graph.get_edge_nodes(self.__cobj)


class Graph(object):
    """
    """
    def __init__(self):
        """
        """
        self.__cobj = clads_graph.initialize()

    def __len__(self):
        """
        """
        nodes, edges = self.size()
        return nodes

    def size(self):
        """
        """
        return clads_graph.size(self.__cobj)

    def get_cobj(self):
        """
        """
        return self.__cobj

    def add_node(self, info):
        """
        """
        return clads_graph.add_node(self.__cobj, info)

    def add_edge(self, na, nb, info):
        """
        """
        return clads_graph.add_edge(self.__cobj, na, nb, info)


if __name__ == "__main__":
    """
    """
    # testing
    g = Graph()

    na = Node(g.add_node("john"))
    nb = Node(g.add_node("mary"))
    nc = Node(g.add_node("lucy"))

    print na, na.get_info()
    print nb, nb.get_info()
    print nc, nc.get_info()

    ea = Edge(g.add_edge(na.get_cobj(), nb.get_cobj(), "loves"))
    eb = Edge(g.add_edge(na.get_cobj(), nc.get_cobj(), "loves"))
    ec = Edge(g.add_edge(nb.get_cobj(), nc.get_cobj(), "hates"))

    print ea, Node(ea.get_nodes()[0]).get_info(), \
            Node(ea.get_nodes()[1]).get_info(), \
            ea.get_info()
    print eb, Node(eb.get_nodes()[0]).get_info(), \
            Node(eb.get_nodes()[1]).get_info(), \
            eb.get_info()
    print ec, Node(ec.get_nodes()[0]).get_info(), \
            Node(ec.get_nodes()[1]).get_info(), \
            ec.get_info()
