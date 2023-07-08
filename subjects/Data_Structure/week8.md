# week8 Tree ADT wiki

## 1. Structure
- node
	|Field|Type|Description|
	|---|---|---|
	|`value`|char|노드의 내용|
	|`parent`|node*|부모 또는 형제 노드의 포인터|
	|`left`|node*|자식 노드의 포인터|
	|`right`|node*|형제 노드의 포인터|

- tree
	|Field|Type|Description|
	|---|---|---|
	|`root`|node*|루트 노드의 포인터|
	|`isBinary`|int|이진트리라면 1, 일반트리라면 0|

## 2. Functions
|Function|Return type|Description|
|---|---|---|
|`print(tree* myTree)`|void|Print the nonnull tree.|
|`create(tree** myTree, char root)`|void|Dynamically allocate the tree with root.|
|`getSibling(tree* myTree, char target)`|void|Print siblings.|
|`insertNode(tree* myTree, chat parent, char* list)`|void|Insert children under the parent.|
|`getParent(tree* myTree, char target)`|char|Return the value of parent node.|
|`getChild(tree* myTree, char target)`|void|Print children if exist.|
|`levelOfNode(tree* myTree, char target, int level)`|int|Return level of the node.|
|`levelOfTree(tree* myTree, int level)`|int|Return maximum level of the tree.|
|`delete(tree* myTree, char target)`|void|Delete the target node.|
|`getAncestors(tree* myTree, char target)`|void|Print ancestors.|
|`getDescendants(tree* myTree, char target)`|void|Print descendants.|
|`degreeOfNode(tree* myTree, char target)`|void|Print degree of the node.|
|`degreeOfTree(tree* myTree)`|int|Return maximum degree of the tree.|
|`countNode(tree* myTree)`|int|Return the number of node in tree.|
|`insertSibling(tree* myTree, char target, char* list)`|Insert siblings of the target node.|
|`joinTrees(char root, tree* tree1, tree* tree2)`|tree*|Return new tree with new root with two trees as children.|
|`clear(tree** myTree)`|void|Back to before create state.|


## 2-1. more functions
|Function|Return type|Description|
|---|---|---|
|`status(tree* myTree)`|void|Print either "No tree" or "No data", or print elements.|
|`isIn(tree* myTree, char value)`|int|Return 1 if there is node with such value.|
|`find(tree* myTree, char value)`|node*|Return the node of value.|
|`countSibling(tree* myTree, char target)`|int|Return the number of siblings.|
|`split(char* input)`|char*|Split comma seperated values in input.|
|`getElements(node* current)`|Print all siblings and children.|

## 3. Errors
|Error|Description|
|---|---|
|*ERROR: No tree*|트리가 없는 상황에서 삽입 하는 경우|
|*ERROR: No root*|루트가 없는 상황에서 삽입 하는 경우|
|*ERROR: Parent node does not exist*|입력한 부모 노드가 없어 삽입 하지 못하는 경우|
|*ERROR: Too many children/siblings for binary tree*|이진 트리에서 자식이 3개 이상이 되어 삽입할 수 없는 경우|
|*ERROR: Such node doesn't exist*|작업을 수행해야하는 노드가 없는 경우|
|*ERROR: Only empty node can be deleted*|부모 노드를 삭제하려는 경우|
|*ERROR: Cannot merge NULL tree*|할당받지 않은 트리를 합치려는 경우|
|*ERROR: Root already exists*|루트가 이미 있는 트리에 루트를 만드려는 경우|
|*ERROR: Cannot merge one same tree*|같은 트리를 합치려는 경우|


# 4. 이진 트리를 위한 기능들
- `create()` 시 이진트리 여부를 물어봄
- 자식, 형제 삽입 시 개수 제한
- 트리를 합칠 때 두 트리 모두 이진 트리이면 합친 트리도 이진트리로 설정