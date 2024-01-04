#ifndef TREE_H
#define TREE_H

class Tree {

public:
  Tree();

  void TreeRootNode(std::string VID, std::string A, std::string CID, int LC, int RC, bool IR, std::string PCID, std::string PD, int Y, std::string CD, bool IVO, std::string GC);
  void AddTreeNode(std::string VID, std::string A, std::string CID, int LC, int RC, bool IR, std::string PCID, std::string PD, int Y, std::string CD, bool IVO, std::string GC, Tree * ParentTarget);

  Tree * getTreeNode(Tree *Current, std::string TargetCommentID);


  // GETTERS
  Tree * getRootPointer() const;

  std::string getVideo_ID(Tree* Pointer) const;
  std::string getAuthor(Tree* Pointer) const;
  std::string getComment_ID(Tree* Pointer) const;
  int getLike_Count(Tree* Pointer) const;
  int getReply_Count(Tree* Pointer) const;
  bool getIs_Reply(Tree* Pointer) const;
  std::string getParent_Comment_ID(Tree* Pointer) const;
  std::string getPublished_Date(Tree* Pointer) const;
  int getSimpleDate(Tree* Pointer) const;
  std::string getCrawled_Date(Tree* Pointer) const;
  bool getIs_Video_Owner(Tree* Pointer) const;
  std::string getComment(Tree* Pointer) const;

  // ADD + HIDDEN
  void AddLike_Count(Tree *Pointer);
  void AddReplies_Count(Tree *Pointer);
  void HiddenTrue(Tree *Pointer);
  void HiddenFalse(Tree *Pointer);

  void Print(Tree *Pointer, int Indent, std::ostream& out_str);
  void Delete();

private:  // REPRESENTATION (member variables)
  
  std::string Video_ID;
  std::string Author;
  std::string Comment_ID;
  int Like_Count;
  int Reply_Count;
  bool Is_Reply;
  std::string Parent_Comment_ID;
  std::string Published_Date;
  int SimpleDate;
  std::string Crawled_Date;
  bool Is_Video_Owner;
  std::string Comment;
  bool Hidden = false;

  Tree* TreeNodeRoot;
  Tree* TreeNode;

  Tree* Parent;
  std::vector<Tree *> Below;
  std::vector<Tree *> DeletingStorage;
  Tree* Root;

};

#endif


