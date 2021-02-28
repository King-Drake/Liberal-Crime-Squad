#pragma once

struct Deprecatedrecruitst
{
	long recruiter_id;
	DeprecatedCreature* recruit;
	//short timeleft;
	//char level;
	char eagerness1;
	//, task;
	//Deprecatedrecruitst();
	Deprecatedrecruitst(DeprecatedCreature * cr, int id);
	~Deprecatedrecruitst();
	char eagerness();
};
