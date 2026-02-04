
data TriTree a = Empty3 | Node3 a (TriTree a) (TriTree a) (TriTree a)
    deriving (Show, Eq, Ord)


tritree = Node3 10 (Node3 3 (Node3 5 Empty3 Empty3 Empty3) (Node3 8 (Node3 1 Empty3 Empty3 Empty3) Empty3 (Node3 2 Empty3 Empty3 Empty3)) (Node3 9 Empty3 Empty3 Empty3))
                   (Node3 7 (Node3 11 Empty3 Empty3 Empty3) Empty3 (Node3 13 Empty3 Empty3 Empty3)) 
                   (Node3 12 (Node3 6 Empty3 Empty3 Empty3) Empty3 (Node3 4 Empty3 Empty3 Empty3))

triSize Empty3 = 0
triSize (Node3 a Empty3 Empty3 Empty3) = 1
triSize (Node3 a left middle right) = 1 + triSize left + triSize middle + triSize right

triLevels _ Empty3 = []
triLevels k (Node3 a left mid right) =
    if k == 0 then [a] else triLevels (k-1) left ++ triLevels (k-1) mid ++ triLevels (k-1) right

-- data NTree a = Nil | Node a [NTree a]
--  deriving (Show)

-- t1 = Node 10 [Node 3 [Node 5 [Nil], Node 8 [Node 1 [Nil], Node 2 [Nil]], Node 9 [Nil]], Node 7 [Node 11 [Nil], Node 13 [Nil]], Node 12 [Node 6 [Nil], Node 4 [Nil]]]
-- t2 = Node 10 [Node 3 [Node 5 [Node 1 [Nil], Node 2 [Nil]], Node 8 [Node 1 [Nil], Node 2 [Nil]], Node 9 [Nil]], Node 7 [Node 11 [Nil], Node 13 [Nil]], Node 12 [Node 6 [Nil], Node 4 [Nil]]]

-- getLevel Nil _ = []
-- getLevel (Node value _) 0 = [value]
-- getLevel (Node value children) k = concatMap (`getLevel` (k - 1)) children

-- numOfNodes Nil = 0
-- numOfNodes (Node grandFather parents) 
--         = (length $ filter (\parent -> (sum $ getLevel parent 1) == grandFather) parents)
--         + (sum $ map numOfNodes parents)


data BTree = Empty | Node Int BTree BTree

t11 = Node 8 (Node 3 (Node 1 Empty Empty) (Node 4 Empty Empty)) (Node 10 (Node 9 Empty Empty) (Node 14 Empty Empty))
t22 = Node 8 (Node 3 (Node 9 Empty Empty) (Node 10 Empty Empty)) (Node 10 (Node 11 Empty Empty) (Node 14 Empty Empty))

getLevel Empty _ = []
getLevel (Node value _ _) 0 = [value]
getLevel (Node _ left right) k = getLevel left (k - 1) ++ getLevel right (k - 1)

grandchildrenIncreased Empty = True
grandchildrenIncreased t@(Node val left right) =
    all (> val) (getLevel t 2) && grandchildrenIncreased left && grandchildrenIncreased right


traverseDFS Empty = []
traverseDFS (Node val left right) = traverseDFS left ++ [val] ++ traverseDFS right

isSymmetric Empty = True
isSymmetric (Node _ left right) = traverseDFS left == reverse (traverseDFS right)


data NestedList = Elem Int | List [NestedList]

flatten (Elem a)= [a]
flatten (List elements) = concatMap flatten elements