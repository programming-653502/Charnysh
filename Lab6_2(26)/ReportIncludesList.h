//---------------------------------------------------------------------------

#ifndef ReportIncludesListH
#define ReportIncludesListH

struct ReportItem
{
	int Cell;
	ReportItem* next;
};
class ReportList
{
	ReportItem *First, *Next;
	int Size;
	public:
	ReportList();
	void PushItem(int No);
	int PopItem();
    int getSize();
	~ReportList();
};
//---------------------------------------------------------------------------
#endif
