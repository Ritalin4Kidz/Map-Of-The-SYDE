#pragma once
#include "SYDEstdafx.h"

class __Quest {
public:
	__Quest() {}
	__Quest(vector<string> details, string tag) { m_details = details;  m_tag = tag; }
	__Quest(vector<string> details, string tag, int _amtReq) { m_details = details;  m_tag = tag; amtRequired = _amtReq; }
	virtual ~__Quest() {}

	bool getGiven() { return m_Given; }
	void setGiven(bool a) { m_Given = a; }

	bool getFinished() { return m_Finished; }
	void setFinished(bool a) { m_Finished = a; }

	string getTag() { return m_tag; }
	vector<string> getDetails() { return m_details; }

	void setAmtDone(int a_new) { amtDone = a_new; }
	int getAmtDone() { return amtDone; }

	int getAmtRequired() { return amtRequired; }
private:
	bool m_Given = false;
	bool m_Finished = false;
	vector<string> m_details = {""};
	string m_tag;

	int amtDone = 0;
	int amtRequired = 1;
};