import os
import sys
import zlib


"""
I ran the following command:
strace -f python3 topo_order_commits.py 2>&1 | grep exec
The only output is shell launching the python interpreter
"""


class CommitNode:
    def __init__(self, commit_hash, branches=[]):
        """
        :type commit_hash: str
        """

        self.commit_hash = commit_hash
        self.parents = set()
        self.children = set()
        self.branches = branches

    def __lt__(self, other):
        return self.commit_hash < other.commit_hash


def topo_order_commits():
    # raise NotImplementedError
    global git_path
    git_path = find_git()

    branches = git_path + '/refs/heads/'
    if os.path.isdir(branches):  # check if the folder is there
        branch_dict = get_branches(branches)
    else:
        exit(1)

    stack = []  # for DFS
    global v_nodes
    v_nodes = {}  # the nodes that have already been visited

    for branch in branch_dict:  # create all branches
        if branch not in v_nodes:
            a = CommitNode(branch, branch_dict[branch])
            v_nodes[branch] = a
            stack.append(a)

        else:
            a = v_nodes[branch]
            a.branches.append(branch)

    global root
    root = []
    build_graph(stack[:])  # build the commit graph

    v_nodes = set()

    res = topo_sort(root)

    sticky = False

    for i in range(len(res)):
        a = res[i]
        c = a.commit_hash

        if i < len(res) - 1:
            next_node = res[i + 1]

        if sticky:
            print('=', end='')
            children = [x.commit_hash for x in sorted(a.children)]
            print(*children)
            sticky = False

        if len(a.branches) == 0:
            print(c)
        else:
            print(c, ' '.join(sorted([x for x in a.branches])))

        if next_node not in a.parents and i < len(res) - 1:
            parents = [x.commit_hash for x in a.parents]
            print(*parents, end='')
            print('=\n')
            sticky = True


def topo_sort(root):
    res = list()
    stack = sorted(root)

    while len(stack) > 0:
        a = stack[-1]
        v_nodes.add(a)

        c = [x for x in a.children if x not in v_nodes]

        if len(c) == 0:
            a = stack.pop()
            res.append(a)
            continue
        stack.append(c[0])
    return(res)


def find_git():  # looking for the .git folder
    cur_dir = os.getcwd()

    while cur_dir != '/':
        if '.git' in os.listdir(cur_dir):
            return os.path.join(cur_dir, '.git')

        cur_dir = os.path.dirname(cur_dir)

    sys.stdout.write('Not inside a Git repository\n')
    exit(1)


def get_branches(branch_path):
    branches = {}
    # get all the files in ~/refs/heads, store their hashes in a dict
    for root, dirs, files in os.walk(branch_path):
        for f in files:
            path = os.path.relpath(os.path.join(root, f), branch_path)
            path = os.path.join(branch_path, path)
            commit = open(path, 'r')

            c = commit.readline().strip('\n')
            f = path[len(branch_path):]
            arr = []
            if c in branches:
                arr = branches[c]
                arr.append(f)
                branches[c] = arr
            else:
                arr.append(f)
                branches[c] = arr

            commit.close()

    return branches


def build_graph(stack):  # build graph with dfs

    while stack:
        a = stack.pop()
        c = a.commit_hash
        folder = c[:2] + '/' + c[2:]
        path = git_path + '/objects/' + folder

        with open(path, 'rb') as file:
            inp = file.read()
            res = zlib.decompress(inp).decode()

        file.close()

        for line in res.splitlines():
            ln = line.split(' ')
            if ln[0] == 'parent' and ln[1] and len(ln) == 2:
                h = ln[1]
                if h not in v_nodes:
                    n = CommitNode(h)
                    a.parents.add(n)
                    n.children.add(a)
                    stack.append(n)
                    v_nodes[h] = n
                else:
                    n = v_nodes[h]
                    a.parents.add(n)
                    n.children.add(a)

        if len(a.parents) == 0:
            root.append(a)


if __name__ == '__main__':
    topo_order_commits()
