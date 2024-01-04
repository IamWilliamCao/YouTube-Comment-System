#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include "Tree.h"

// Default Constructor
Tree::Tree() {
  TreeNodeRoot = NULL;
};

//Creates the Tree's Main Root
void Tree::TreeRootNode(std::string VID, std::string A, std::string CID, int LC, int RC, bool IR, std::string PCID, std::string PD, int Y, std::string CD, bool IVO, std::string GC) {
  TreeNodeRoot = new Tree;
  TreeNodeRoot->Parent = NULL;
  TreeNodeRoot->Root = TreeNodeRoot;
  TreeNodeRoot->Video_ID = VID;
  TreeNodeRoot->Author = A;
  TreeNodeRoot->Comment_ID = CID;
  TreeNodeRoot->Like_Count = LC;
  TreeNodeRoot->Reply_Count = RC;
  TreeNodeRoot->Is_Reply = IR;
  TreeNodeRoot->Parent_Comment_ID = PCID;
  TreeNodeRoot->Published_Date = PD;
  TreeNodeRoot->SimpleDate = Y;
  TreeNodeRoot->Crawled_Date = CD;
  TreeNodeRoot->Is_Video_Owner = IVO;
  TreeNodeRoot->Comment = GC;
}

//Creates the Branches
void Tree::AddTreeNode(std::string VID, std::string A, std::string CID, int LC, int RC, bool IR, std::string PCID, std::string PD, int Y, std::string CD, bool IVO, std::string GC, Tree * ParentTarget) {
  TreeNode = new Tree;
  TreeNode->Parent = TreeNodeRoot;
  ParentTarget->Below.push_back(TreeNode);
  TreeNodeRoot->DeletingStorage.push_back(TreeNode);
  TreeNode->Root = TreeNodeRoot;
  TreeNode->Video_ID = VID;
  TreeNode->Author = A;
  TreeNode->Comment_ID = CID;
  TreeNode->Like_Count = LC;
  TreeNode->Reply_Count = RC;
  TreeNode->Is_Reply = IR;
  TreeNode->Parent_Comment_ID = PCID;
  TreeNode->Published_Date = PD;
  TreeNode->SimpleDate = Y;
  TreeNode->Crawled_Date = CD;
  TreeNode->Is_Video_Owner = IVO;
  TreeNode->Comment = GC;
}



/// /// /// /// ///



// GET NODE

Tree * Tree::getTreeNode(Tree *Current, std::string TargetCommentID) {

  Tree * Current2;

  if (Current == NULL)
  {
  return nullptr;
  }

  if (Current->Comment_ID == TargetCommentID)
  {
  return Current;
  }

  int BelowSize = Current->Below.size();
  
  for (int i = 0; i < BelowSize; i++)
  {
  Current2 = getTreeNode(Current->Below[i], TargetCommentID);
  
  if (Current2->Comment_ID == TargetCommentID)
  {
  return Current2;
  }
  
  }

  return Current;
}


// GETTERS

Tree * Tree::getRootPointer() const {
  return TreeNodeRoot->Root;
}

std::string Tree::getVideo_ID(Tree *Pointer) const {
  return Pointer->Video_ID;
}

std::string Tree::getAuthor(Tree *Pointer) const {
  return Pointer->Author;
}

std::string Tree::getComment_ID(Tree *Pointer) const {
  return Pointer->Comment_ID;
}

int Tree::getLike_Count(Tree *Pointer) const {
  return Pointer->Like_Count;
}

int Tree::getReply_Count(Tree *Pointer) const {
  return Pointer->Reply_Count;
}

bool Tree::getIs_Reply(Tree *Pointer) const {
  return Pointer->Is_Reply;
}

std::string Tree::getParent_Comment_ID(Tree *Pointer) const {
  return Pointer->Parent_Comment_ID;
}

std::string Tree::getPublished_Date(Tree *Pointer) const {
  return Pointer->Published_Date;
}

int Tree::getSimpleDate(Tree *Pointer) const {
  return Pointer->SimpleDate;
}

std::string Tree::getCrawled_Date(Tree *Pointer) const {
  return Pointer->Crawled_Date;
}

bool Tree::getIs_Video_Owner(Tree *Pointer) const {
  return Pointer->Is_Video_Owner;
}

std::string Tree::getComment(Tree *Pointer) const {
  return Pointer->Comment;
}

/// /// /// /// ///


// ADD + HIDDEN

void Tree::AddLike_Count(Tree *Pointer) {
  Pointer->Like_Count = Pointer->Like_Count + 1;
}

void Tree::AddReplies_Count(Tree *Pointer) {
  Pointer->Reply_Count = Pointer->Reply_Count + 1;
}

void Tree::HiddenTrue(Tree *Pointer) {
  Pointer->Hidden = true;
}

void Tree::HiddenFalse(Tree *Pointer) {
  Pointer->Hidden = false;
}

//DELETING
void Tree::Delete() {

int DSsize = TreeNodeRoot->DeletingStorage.size();

if (DSsize == 0)
{
  delete TreeNodeRoot;
  return;
}
else 
{
  for (int i = 0; i < DSsize; i++)
  {
    delete TreeNodeRoot->DeletingStorage[i];
  }
  delete TreeNodeRoot;
  return;
}
}

//PRINT
void Tree::Print(Tree *Pointer, int Indent, std::ostream& out_str) {
  
  if (Pointer->Hidden == true)
  {
  return;
  }

  int BelowSize = Pointer->Below.size();

  //PRINT INFO:

  //AUTHOR
  for (int o = 0; o < Indent; o++)
  {
  out_str << "    ";
  }
  out_str << Pointer->Author << " " << Pointer->Published_Date << std::endl;


  //COMMENT
  for (int o = 0; o < Indent; o++)
  {
  out_str << "    ";
  }
  out_str << Pointer->Comment << std::endl;


  //LIKE COUNT
  for (int o = 0; o < Indent; o++)
  {
  out_str << "    ";
  }
  out_str << "\U0001F44D " << Pointer->Like_Count << std::endl;


  //REPLY COUNT
  if (Pointer->Reply_Count != 0)
  {
    for (int o = 0; o < Indent; o++)
    {
    out_str << "    ";
    }
    if (Pointer->Reply_Count == 1)
    {
    out_str << Pointer->Reply_Count << " reply" << std::endl;
    }
    else
    {
    out_str << Pointer->Reply_Count << " replies" << std::endl;
    }
  }



  for (int i = 0; i < BelowSize; i++)
  {
  Print(Pointer->Below[i], Indent+1, out_str);
  }

  if (Pointer->Below.size() == 0)
  {
  return;
  }

}




