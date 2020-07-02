/* To compile:
 c++ -std=c++17 -o result CTCI_4-12_PathsWithSum.cpp
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

struct Node {
    int val = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    
    Node(int val) : val{val} {}
};

void print_tree_inorder(Node* curr_node) {
    if (!curr_node) return;
    print_tree_inorder(curr_node->left);
    std::cout << curr_node->val << " ";
    print_tree_inorder(curr_node->right);
}

void print_tree_preorder(Node* curr_node) {
    if (!curr_node) return;
    std::cout << curr_node->val << " ";
    print_tree_preorder(curr_node->left);
    print_tree_preorder(curr_node->right);
}

void print_tree_postorder(Node* curr_node) {
    if (!curr_node) return;
    print_tree_postorder(curr_node->left);
    print_tree_postorder(curr_node->right);
    std::cout << curr_node->val << " ";
}

void levelorder_traversal(Node *root) {
    std::queue <Node*> que;
    Node *item;
    que.push(root);
    while(!que.empty()){
        item = que.front();
        std::cout << item->val << " ";
        if(item->left)
            que.push(item->left);
        if(item->right)
            que.push(item->right);
        que.pop();
    }
}

Node* build_tree(std::vector<int>& vals, Node* root, int i) {
    int n = vals.size();
    if (i < vals.size()) {
        Node* temp = new Node(vals[i]);
        root = temp;
        root->left = build_tree(vals, root->left, 2 * i + 1);
        root->right = build_tree(vals, root->right, 2 * i + 2);
    }
    return root;
}

Node* running_sum(Node* orig_node, int parent_val) {
    if (!orig_node) return nullptr;
        
    Node* curr_new = new Node(orig_node->val + parent_val);
    curr_new->left = running_sum(orig_node->left, curr_new->val);
    curr_new->right = running_sum(orig_node->right, curr_new->val);
    
    return curr_new;
}

void paths_count(Node* rs_root, std::unordered_map<int, int>& rs_map, int& counter, const int& target) {
    
    if (!rs_root) return;
    
    int curr_rs = rs_root->val;

    int target_rs = curr_rs - target;
    int rs_freq = 0;
    if (rs_map.find(target_rs) != rs_map.end()) {
        rs_freq = rs_map.at(target_rs);
    }
    counter += rs_freq;
    
    if (curr_rs == target) counter++;
        
    rs_map[curr_rs]++;
    
    paths_count(rs_root->left, rs_map, counter, target);
    paths_count(rs_root->right, rs_map, counter, target);
    
    if (rs_map[curr_rs] <= 1) {
        rs_map.erase(curr_rs);
    } else {
        rs_map[curr_rs]--;
    }
}


int main() {
    
    std::vector<int> vals{1, 2, 3, 4, 2, -2, -1, 5, 4, 2};
    Node* root = build_tree(vals, 0, false);
    
    /* Print traversals of the original tree */
    //std::cout << "Root:\n";
    //std::cout << root->val << "\n";
    //std::cout << "Inorder:\n";
    //print_tree_inorder(root);
    //std::cout << "\nPreorder:\n";
    //print_tree_preorder(root);
    //std::cout << "\nPostorder:\n";
    //print_tree_postorder(root);
    //std::cout << "\nLevel Order:\n";
    //levelorder_traversal(root);
    //std::cout << "\n";
    
    
    Node* rs_root = running_sum(root, 0);
    
    /* Print traversals of the running sum tree */
    //std::cout << "--------------------------------\n";
    //std::cout << "Root:\n";
    //std::cout << rs_root->val << "\n";
    
    //std::cout << "Inorder:\n";
    //print_tree_inorder(rs_root);
    //std::cout << "\nPreorder:\n";
    //print_tree_preorder(rs_root);
    //std::cout << "\nPostorder:\n";
    //print_tree_postorder(rs_root);
    //std::cout << "\nLevel Order:\n";
    //levelorder_traversal(rs_root);
    //std::cout << "\n";
    
    
    /* Calculate number of paths that sum to target value */
    int counter = 0;
    int target = 4;
    std::unordered_map<int, int> rs_map;
    paths_count(rs_root, rs_map, counter, target);
    
    std::cout << "counter = " << counter << std::endl;
    
    return 0;
}
