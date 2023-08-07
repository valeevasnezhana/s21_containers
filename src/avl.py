from collections import deque
import pygame
import sys
import random

width = 1200
height = 800
pygame.init()
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Binary Tree View')
screen.fill((255, 255, 255))

pygame.display.flip()
clock = pygame.time.Clock()
pygame.font.init()

my_font = pygame.font.SysFont(None, 30)


class TreeNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1
        self.level = 0
        self.main_index = 0
        self.index_in_level = 0


class CircleNode:
    def __init__(self, x=0, y=0, size=20, visible=False, text=''):
        self.x = x
        self.y = y
        self.size = size
        self.visible = visible
        self.text = text

    def draw_node(self):
        if self.visible:
            pygame.draw.circle(screen, color=(0, 0, 0), center=(self.x, self.y), radius=(self.size // 2), width=0)

            text_surface = my_font.render(self.text, True, (255, 255, 255))
            rect = text_surface.get_rect()
            # pygame.draw.rect(text_surface, (255, 255, 255), rect, 1)
            screen.blit(text_surface, (self.x - rect.center[0], self.y - rect.center[1]))


class AVLTree:

    def insert_node(self, root: TreeNode, key):

        if not root:
            return TreeNode(key)
        elif key < root.key:
            root.left = self.insert_node(root.left, key)
        else:
            root.right = self.insert_node(root.right, key)

        root.height = 1 + max(self.get_height(root.left),
                              self.get_height(root.right))

        # Update the balance factor and balance the tree
        balance_factor = self.get_balance(root)
        if balance_factor > 1:
            if key < root.left.key:
                return self.right_rotate(root)
            else:
                root.left = self.left_rotate(root.left)
                return self.right_rotate(root)

        if balance_factor < -1:
            if key > root.right.key:
                return self.left_rotate(root)
            else:
                root.right = self.right_rotate(root.right)
                return self.left_rotate(root)

        return root

    def delete_node(self, root, key):

        if not root:
            return root
        elif key < root.key:
            root.left = self.delete_node(root.left, key)
        elif key > root.key:
            root.right = self.delete_node(root.right, key)
        else:
            if root.left is None:
                temp = root.right
                return temp
            elif root.right is None:
                temp = root.left
                return temp
            temp = self.get_min_value_node(root.right)
            root.key = temp.key
            root.right = self.delete_node(root.right,
                                          temp.key)
        if root is None:
            return root

        # Update the balance factor of nodes
        root.height = 1 + max(self.get_height(root.left),
                              self.get_height(root.right))

        balance_factor = self.get_balance(root)

        # Balance the tree
        if balance_factor > 1:
            if self.get_balance(root.left) >= 0:
                return self.right_rotate(root)
            else:
                root.left = self.left_rotate(root.left)
                return self.right_rotate(root)
        if balance_factor < -1:
            if self.get_balance(root.right) <= 0:
                return self.left_rotate(root)
            else:
                root.right = self.right_rotate(root.right)
                return self.left_rotate(root)
        return root

    def left_rotate(self, z):
        y = z.right
        t2 = y.left
        y.left = z
        z.right = t2
        z.height = 1 + max(self.get_height(z.left),
                           self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left),
                           self.get_height(y.right))
        return y

    def get_min_value_node(self, root):
        if root is None or root.left is None:
            return root
        return self.get_min_value_node(root.left)

    # Function to perform right rotation
    def right_rotate(self, z):
        y = z.left
        t3 = y.right
        y.right = z
        z.left = t3
        z.height = 1 + max(self.get_height(z.left),
                           self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left),
                           self.get_height(y.right))
        return y

    @staticmethod
    def get_height(root):
        if not root:
            return 0
        return root.height

    def get_balance(self, root):
        if not root:
            return 0
        return self.get_height(root.left) - self.get_height(root.right)

    def print_helper(self, curr_ptr):
        if curr_ptr is not None:
            self.print_helper(curr_ptr.left)
            print(curr_ptr.key)
            self.print_helper(curr_ptr.right)

    @staticmethod
    def find_levels(root, circle_nodes_: list[list[CircleNode]]):
        if root:
            q: deque[TreeNode] = deque()
            root.main_index = 0
            q.append(root)
            level = 0
            while q:
                for i in range(len(q)):
                    popping = q.popleft()
                    if popping:
                        popping.level = level
                        q.append(popping.left)
                        if popping.left:
                            popping.left.main_index = popping.main_index * 2 + 1
                        q.append(popping.right)
                        if popping.right:
                            popping.right.main_index = popping.main_index * 2 + 2
                        circle_nodes_[level][popping.main_index - int(2 ** level) + 1].visible = True
                        circle_nodes_[level][popping.main_index - int(2 ** level) + 1].text = str(popping.key)
                level += 1


my_tree = AVLTree()
root2 = None
nums1 = [5, 10, 3, 7, 4, 9, 32, 22, 6, 2, 30, 300, 392, 0, 1, 8]
for num in nums1:
    root2 = my_tree.insert_node(root2, num)
# my_tree.print_helper(root2)


def draw_tree(root1):
    screen.fill((255, 255, 255))
    circle_nodes: list[list[CircleNode]] = [
        [CircleNode(size=50) for _ in range(int(2 ** level))] for level in range(my_tree.get_height(root1))
    ]

    my_tree.find_levels(root1, circle_nodes)
    distance_between_nodes = 5
    if circle_nodes and circle_nodes[-1]:
        for i, node in enumerate(circle_nodes[-1]):
            circle_nodes[-1][i].x = 50 + i * (distance_between_nodes + node.size)
            circle_nodes[-1][i].y = height - 200
            # circle_nodes[-1][i].draw_node()

    i = my_tree.get_height(root1) - 2
    while i >= 0:
        for j, node in enumerate(circle_nodes[i]):
            circle_nodes[i][j].x = (circle_nodes[i + 1][j * 2].x + circle_nodes[i + 1][j * 2 + 1].x) // 2
            circle_nodes[i][j].y = circle_nodes[i + 1][j * 2].y - node.size - distance_between_nodes
            if circle_nodes[i][j].visible and circle_nodes[i + 1][j * 2].visible:
                pygame.draw.line(
                    screen,
                    (0, 0, 0),
                    (circle_nodes[i][j].x, circle_nodes[i][j].y),
                    (circle_nodes[i + 1][j * 2].x, circle_nodes[i + 1][j * 2].y)
                )
            if circle_nodes[i][j].visible and circle_nodes[i + 1][j * 2 + 1].visible:
                pygame.draw.line(
                    screen,
                    (0, 0, 0),
                    (circle_nodes[i][j].x, circle_nodes[i][j].y),
                    (circle_nodes[i + 1][j * 2 + 1].x, circle_nodes[i + 1][j * 2 + 1].y)
                )
            # circle_nodes[i][j].draw_node()
        i -= 1
    for level in circle_nodes:
        for node in level:
            node.draw_node()
    pygame.display.update()


draw_tree(root2)
random.shuffle(nums1)
ind = 0

# for num in nums1:
#     root2 = my_tree.delete_node(root2, num)
#     print(num)

print(nums1[ind])

while True:
    dt = clock.tick(60) / 1000
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        # if event.type == pygame.MOUSEBUTTONDOWN:
        #     draw_tree(root2)
        if event.type == pygame.MOUSEBUTTONDOWN:
            if ind < len(nums1):
                root2 = my_tree.delete_node(root2, nums1[ind])
                ind += 1
            draw_tree(root2)
            if ind < len(nums1):
                print(nums1[ind])
