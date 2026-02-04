int maxSumOfNonAdjacent() const{
std::pair<int, int> pair = maxSumOfNonAdjacent();
return std::max(pair.first, pair.second);
}

private:
static std::pair<int, int> maxSumOfNonAdjacent(Tree const &tree){
	std::pair<int,int> rootPair(tree.m_root, 0);
	for(Tree const &child : tree.children()){
		std::pair<int,int> result = maxSumOfNonAdjacent(child);
		rootPair.first += result.first;
		rootPair.second += std::max(result.first, result.second);
	}
	return rootPair;
}
