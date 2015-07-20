#include "list.h"
struct Node
{
	ElementType Element;
	Position    Next;
};
/* return ture of L is empty */
 int  IsEmpty(List L)
 {
	return L->Next ==NULL;//
 }
 /* return true of P is the last position in list L */
 /* parameter L is unused in this implementation */
 int IsLast(Position P,List L)
 {
	return P->Next == NULL;
 }
 /* return position of x in L ,NULL is not found */
 Position Find(ElementType X,List L)
 {
	Position P;
	
	P=L->Next;
	while(P!=NULL&&P->Element != X)
	P=P->Next;
	
	return P;
 }
 /* if X is not found ,then next field of returned */
 Position FindPrevious(ElementType X, List L)
 {
	Position P;
	
	P=L;
	while(P->Next!=NULL&&P->Next->Element != X)
	P=P->Next;
	
	return P;
 }
 
 /* delete first occurrence of x frome a list */
 /* assume use of a header node */
 void Delete(ElementType X,List L)
 {
	Position P, TmpCell;
	
	P=FindPrevious(X,L);
	if(!IsLast(P,L))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
 }
 
 /* insert  */
 void Insert(ElementType X,List L,Position P)
 {
	Position TmpCell;
	TmpCell= malloc(sizeof(struct Node));
	if(TmpCell==NULL)
	{
		FatalError("Out of space!!!");
	}
	TmpCell->Element =X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
 }