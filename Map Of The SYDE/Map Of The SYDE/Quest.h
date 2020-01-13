#pragma once
#include "SYDEstdafx.h"

class __Quest {
public:
	__Quest() {}
	__Quest(string details, string tag) { m_details = details;  m_tag = tag; }
	virtual ~__Quest() {}

	bool getGiven() { return m_Given; }
	void setGiven(bool a) { m_Given = a; }

	bool getFinished() { return m_Finished; }
	void setFinished(bool a) { m_Finished = a; }

	string getTag() { return m_tag; }
	string getDetails() { return m_details; }
private:
	bool m_Given = false;
	bool m_Finished = false;
	string m_details = "";
	string m_tag;
};