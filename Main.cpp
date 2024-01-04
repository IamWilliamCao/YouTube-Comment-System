#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include "Tree.h"



 // // // // // // // // // // // // // // // // // // 

 // FUNCTIONS

void InfoSeparating(std::string& ContentMain, std::vector<std::vector<std::string> > & Vector, std::vector<std::string> SmollVector, int WordCount, int MaxWordCount)
{

	int CurrentLength = 0;
	std::string Content = ContentMain;
	int MainLength = ContentMain.length();
	while (CurrentLength != MainLength)
	{

	  //Whole_Comment
	  std::size_t WholeCommentStart = Content.find("{");
		std::size_t WholeCommentEnd = Content.find("}");
		std::string WholeComment = Content.substr(WholeCommentStart, WholeCommentEnd+1); 

		int WholeCommentSize = WholeComment.length();
		WordCount = WordCount + WholeCommentSize;

		//Video_ID
		std::size_t VideoIDStart = WholeComment.find("\"video_id\": ");
		std::size_t VideoIDEnd = WholeComment.find(" \"author\":");
		std::string VideoIDSection = WholeComment.substr(VideoIDStart+13, VideoIDEnd-VideoIDStart-15); 
		SmollVector.push_back(VideoIDSection);

		//Author
		std::size_t AuthorStart = WholeComment.find("\"author\": ");
		std::size_t AuthorEnd = WholeComment.find(" \"comment_id\":");
		std::string AuthorSection = WholeComment.substr(AuthorStart+11, AuthorEnd-AuthorStart-13); 
		SmollVector.push_back(AuthorSection);

		//Comment_ID
		std::size_t CommentIDStart = WholeComment.find("\"comment_id\": ");
		std::size_t CommentIDEnd = WholeComment.find(" \"like_count\":");
		std::string CommentIDSection = WholeComment.substr(CommentIDStart+15, CommentIDEnd-CommentIDStart-17); 
		SmollVector.push_back(CommentIDSection);

		//Like_Count
		std::size_t LikeCountStart = WholeComment.find("\"like_count\": ");
		std::size_t LikeCountEnd = WholeComment.find(" \"reply_count\":");
		std::string LikeCountSection = WholeComment.substr(LikeCountStart+14, LikeCountEnd-LikeCountStart-15); 
		SmollVector.push_back(LikeCountSection);

		//Reply_Count
		std::size_t ReplyCountStart = WholeComment.find("\"reply_count\": ");
		std::size_t ReplyCountEnd = WholeComment.find(" \"is_reply\":");
		std::string ReplyCountSection = WholeComment.substr(ReplyCountStart+15, ReplyCountEnd-ReplyCountStart-16); 
		SmollVector.push_back(ReplyCountSection);

		//Is_Reply
		std::size_t IsReplyStart = WholeComment.find("\"is_reply\": ");
		std::size_t IsReplyEnd = WholeComment.find(" \"parent_comment_id\":");
		std::string IsReplySection = WholeComment.substr(IsReplyStart+12, IsReplyEnd-IsReplyStart-13); 
		
			if (IsReplySection == "false") 
			{
				SmollVector.push_back("0");
			}
			else 
			{
				SmollVector.push_back("1");
			}

		//Parent_Comment_ID
		std::size_t ParentCommentIDStart = WholeComment.find("\"parent_comment_id\": ");
		std::size_t ParentCommentIDEnd = WholeComment.find(" \"published_date\":");
		std::string ParentCommentIDSection = WholeComment.substr(ParentCommentIDStart+22, ParentCommentIDEnd-ParentCommentIDStart-24); 

			if (ParentCommentIDSection.length() == 0)
			{
				SmollVector.push_back("\"\"");
			}
			else
			{
				SmollVector.push_back(ParentCommentIDSection);
			}

		//Published_Date
		std::size_t PublishedDateStart = WholeComment.find("\"published_date\": ");
		std::size_t PublishedDateEnd = WholeComment.find(" \"crawled_date\":");
		std::string PublishedDateSection = WholeComment.substr(PublishedDateStart+19, PublishedDateEnd-PublishedDateStart-21); 
		SmollVector.push_back(PublishedDateSection);
		SmollVector.push_back("000");

		//Crawled_Date
		std::size_t CrawledDateStart = WholeComment.find("\"crawled_date\": ");
		std::size_t CrawledDateEnd = WholeComment.find(" \"is_video_owner\":");
		std::string CrawledDateSection = WholeComment.substr(CrawledDateStart+17, CrawledDateEnd-CrawledDateStart-19); 
		SmollVector.push_back(CrawledDateSection);

		//Is_Video_Owner
		std::size_t IsVideoOwnerStart = WholeComment.find("\"is_video_owner\": ");
		std::size_t IsVideoOwnerEnd = WholeComment.find(" \"comment\":");
		std::string IsVideoOwnerSection = WholeComment.substr(IsVideoOwnerStart+18, IsVideoOwnerEnd-IsVideoOwnerStart-19); 
		
			if (IsVideoOwnerSection == "false") 
			{
				SmollVector.push_back("0");
			}
			else 
			{
				SmollVector.push_back("1");
			}

		//Comment
		std::size_t CommentStart = WholeComment.find("\"comment\": ");
		std::size_t CommentEnd = WholeComment.find("}");
		std::string CommentSection = WholeComment.substr(CommentStart+12, CommentEnd-CommentStart-13); 
		SmollVector.push_back(CommentSection);

		Vector.push_back(SmollVector);
		
		if (WordCount == MaxWordCount)
		{
		return;
		}

		//Reset Vector
		Content.erase(WholeCommentStart, WholeCommentEnd+1);
		SmollVector.clear();
		}

	return;
}





 // // // // // // // // // // // // // // // // // // 

 // MAIN

int main(int argc, char** argv) {

	//INPUT1
	std::ifstream in_str1(argv[1]);

  if (!in_str1.good()) {
  std::cerr << "Can't open " << argv[1] << " to read.\n";
  exit(1);
  }

	//INPUT2
  std::ifstream in_str2(argv[2]);

  if (!in_str2.good()) {
  std::cerr << "Can't open " << argv[2] << " to read.\n";
  exit(1);
  }

  //OUTPUT
  std::ofstream out_str(argv[3]);





 // // // // // // // // // // // // // // // // // // 

 // Variables + Vectors

  //Comments
  std::vector<std::string> IndivComments;
  std::vector< std::vector<std::string> > Comments;

  //Commands
  std::vector<std::string> Command;
  std::vector< std::vector<std::string> > Reply_Video;
  std::vector< std::vector<std::string> > Reply_Comment;
  std::vector< std::vector<std::string> > Likes;
  std::vector< std::vector<std::string> > Delete;
  std::vector< std::vector<std::string> > Display;

  //Trees
  std::vector<Tree> AllTree;


 

 // // // // // // // // // // // // // // // // // // 

 // COMMAND + INPUTS

	std::string StringInput;

  while (in_str2 >> StringInput)
  {	
	  Command.push_back(StringInput);

	  //ID 
		in_str2 >> StringInput;
		Command.push_back(StringInput);

		if(Command[0] == "like_comment")
		{

			//GET MAIN TREE
			std::string TempString = Command[1];
			unsigned long found = TempString.find(".");
				if (found != std::string::npos)
			  {
					std::size_t DotEnd = TempString.find(".");
					TempString = TempString.substr(0, DotEnd); 
				}
			Command.push_back(TempString);

			Likes.push_back(Command);
		
		}
		else if(Command[0] == "delete_comment")
		{

			//GET MAIN TREE
			std::string TempString = Command[1];
			unsigned long found = TempString.find(".");
				if (found != std::string::npos)
			  {
					std::size_t DotEnd = TempString.find(".");
					TempString = TempString.substr(0, DotEnd); 
				}
			Command.push_back(TempString);

			Delete.push_back(Command);

		}
		else if(Command[0] == "display_comment")
		{

			//GET MAIN TREE
			std::string TempString = Command[1];
			unsigned long found = TempString.find(".");
				if (found != std::string::npos)
			  {
					std::size_t DotEnd = TempString.find(".");
					TempString = TempString.substr(0, DotEnd); 
				}
			Command.push_back(TempString);

			//NO DUPLICATE
			int DisplaySize = Display.size();
			bool Duplicate = false;
			for (int j = 0; j < DisplaySize; j++)
			{
				if (Display[j][1] == Command[1])
				{
					Duplicate = true;
				}
			}

			if (Duplicate == false)
			{
				Display.push_back(Command);
			}

		}
		else if(Command[0] == "reply_to_video")
		{

			//User's Name
			in_str2 >> StringInput;
			Command.push_back(StringInput);

				//Comment
				in_str2 >> std::ws;
				if (in_str2.peek() == '"') {
					in_str2.get(); 
					std::getline(in_str2, StringInput, '"'); 
					if (!StringInput.empty() && StringInput.back() == '"') {
						StringInput.pop_back(); 
					}
				}
			Command.push_back(StringInput);
			Reply_Video.push_back(Command);

		}
		else if(Command[0] == "reply_to_comment")
		{

		//Users's ID
		in_str2 >> StringInput;
		Command.push_back(StringInput);

		//User's Name
		in_str2 >> StringInput;
		Command.push_back(StringInput);

			//Comment
			in_str2 >> std::ws;
			if (in_str2.peek() == '"') {
				in_str2.get();
				std::getline(in_str2, StringInput, '"'); 
				if (!StringInput.empty() && StringInput.back() == '"') {
					StringInput.pop_back(); 
				}
			}
		Command.push_back(StringInput);

		//GET MAIN TREE
		std::string TempString = Command[1];
		unsigned long found = TempString.find(".");
			if (found != std::string::npos)
		  {
				std::size_t DotEnd = TempString.find(".");
				TempString = TempString.substr(0, DotEnd); 
			}
			
		Command.push_back(TempString);

		Reply_Comment.push_back(Command);
		}

		Command.clear();
	}





 // // // // // // // // // // // // // // // // // // 

 // INPUTS INTO VECTORS

  std::string Json_Content;
  std::string Line;
  while (std::getline(in_str1, Line)) 
  {
  	Json_Content += Line;
  }

  in_str1.close();
  
  //SEPARATING INFO
  int Json_Content_Length = Json_Content.length();
  InfoSeparating(Json_Content, Comments, IndivComments, 0, Json_Content_Length);





 // // // // // // // // // // // // // // // // // // 

 // CREATING TREES

  int VectorSize = Comments.size();

  for (int i = 0; i < VectorSize; i++)
  {

  	//TREE CREATION
  	Tree a;

  	//IF A MAIN COMMENT
  	if (Comments[i][6] == "\"\"")
  	{
  	a.TreeRootNode(Comments[i][0], Comments[i][1], Comments[i][2], stoi(Comments[i][3]), stoi(Comments[i][4]), stoi(Comments[i][5]), Comments[i][6], Comments[i][7], stoi(Comments[i][8]), Comments[i][9], stoi(Comments[i][10]), Comments[i][11]);
  	}

  	//CHECK FOR THE END
  	if (i+1 == VectorSize)
  	{
  	AllTree.push_back(a);
  	break;
  	}

  	//IF A REPLY COMMENT
  	if (Comments[i+1][6] != "\"\"")
  	{
	  	i++;
	  	while (Comments[i][6] != "\"\"")
	  	{

		  	a.AddTreeNode(Comments[i][0], Comments[i][1], Comments[i][2], stoi(Comments[i][3]), stoi(Comments[i][4]), stoi(Comments[i][5]), Comments[i][6], Comments[i][7], stoi(Comments[i][8]), Comments[i][9], stoi(Comments[i][10]), Comments[i][11], a.getTreeNode(a.getRootPointer(), Comments[i][6]));

		  	if (i == VectorSize-1)
		  	{
		  	break;
		  	}

		  	if (i > VectorSize-1)
		  	{
		  	break;
		  	}

		  	if (Comments[i+1][6] != "\"\"")
	  		{
	  		i++;
	  		}
	  		else
	  		{
	  		break;
	  		}
	  	}
  	}
  	AllTree.push_back(a);
  }





 // // // // // // // // // // // // // // // // // // 

 // USING THE COMMANDS GIVEN

	int Reply_VideoSize = Reply_Video.size();
	int Reply_CommentSize = Reply_Comment.size();
	int LikesSize = Likes.size();
	int DeleteSize = Delete.size();
	int DisplaySize = Display.size();
	
	//REPLY TO VIDEO
	for (int i = 0; i < Reply_VideoSize; i++)
	{
	Tree a;
	a.TreeRootNode("VIDEO_ID", Reply_Video[i][2], Reply_Video[i][1], 0, 0, 0, "\"\"", "0 seconds ago", 0, "Crawled_Date", 0, Reply_Video[i][3]);
	AllTree.push_back(a);
	}

	//REPLY TO COMMENT
	for (int o = 0; o < Reply_CommentSize; o++)
	{
		//FIND TREE 
		for (unsigned int i = 0; i < AllTree.size(); i++)
	  {
			if (AllTree[i].getComment_ID(AllTree[i].getRootPointer()) == Reply_Comment[o][5])
			{
				AllTree[i].AddTreeNode("VIDEO_ID", Reply_Comment[o][3], Reply_Comment[o][2], 0, 0, 1, Reply_Comment[o][1], "0 seconds ago", 0, "Crawled_Date", 0, Reply_Comment[o][4], AllTree[i].getTreeNode(AllTree[i].getRootPointer(), Reply_Comment[o][1]));
				AllTree[i].AddReplies_Count(AllTree[i].getTreeNode(AllTree[i].getRootPointer(), Reply_Comment[o][1]));
			}
	  }
	}

	//LIKES
	for (int o = 0; o < LikesSize; o++)
	{
		//FIND TREE 
		for (unsigned long i = 0; i < AllTree.size(); i++)
	  {
			if (AllTree[i].getComment_ID(AllTree[i].getRootPointer()) == Likes[o][2])
			{
				AllTree[i].AddLike_Count(AllTree[i].getTreeNode(AllTree[i].getRootPointer(), Likes[o][1]));
			}
	  }
	}

	//DELETE
	for (int o = 0; o < DeleteSize; o++)
	{
		//FIND TREE 
		for (unsigned long i = 0; i < AllTree.size(); i++)
	  {
			if (AllTree[i].getComment_ID(AllTree[i].getRootPointer()) == Delete[o][2])
			{
			AllTree[i].HiddenTrue(AllTree[i].getTreeNode(AllTree[i].getRootPointer(), Delete[o][1]));
			}
	  }
	}





 // // // // // // // // // // // // // // // // // // 

 // PRINTING

  for (int o = 0; o < DisplaySize; o++)
	{
		//FIND TREE 
		for (unsigned long i = 0; i < AllTree.size(); i++)
	  {

			if (AllTree[i].getComment_ID(AllTree[i].getRootPointer()) == Display[o][2])
			{
			AllTree[i].HiddenFalse(AllTree[i].getTreeNode(AllTree[i].getRootPointer(), Display[o][1]));
			AllTree[i].Print(AllTree[i].getTreeNode(AllTree[i].getRootPointer(), Display[o][1]), 0, out_str);
			}
	  }
	}

 	//DELETING
  for (unsigned long i = 0; i < AllTree.size(); i++)
  {
 	AllTree[i].Delete();
 	}

return 0;
}

	

