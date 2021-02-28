
enum IncomeType         // the below names are used in fundreport() in lcsmonthly.cpp
{                       // new types added without updating fundreport() will show as "Other Income"
	INCOME_BROWNIES,     // "Brownies"
	INCOME_CARS,         // "Car Sales"
	INCOME_CCFRAUD,      // "Credit Card Fraud"
	INCOME_DONATIONS,    // "Donations"
	INCOME_SKETCHES,     // "Drawing Sales"
	INCOME_EMBEZZLEMENT, // "Embezzlement"
	INCOME_EXTORTION,    // "Extortion"
	INCOME_HUSTLING,     // "Hustling"
	INCOME_PAWN,         // "Pawning Goods"
	INCOME_PROSTITUTION, // "Prostitution"
	INCOME_BUSKING,      // "Street Music"
	INCOME_THIEVERY,     // "Thievery"
	INCOME_TSHIRTS,      // "T-Shirt Sales"
	INCOMETYPENUM        // # of types of income
};

enum ExpenseType          // the below names are used in fundreport() in lcsmonthly.cpp
{                         // new types added without updating fundreport() will show as "Other Expenses"
	EXPENSE_TROUBLEMAKING, // "Activism"
	EXPENSE_CONFISCATED,   // "Confiscated"
	EXPENSE_DATING,        // "Dating"
	EXPENSE_SKETCHES,      // "Drawing Materials"
	EXPENSE_FOOD,          // "Groceries"
	EXPENSE_HOSTAGE,       // "Hostage Tending"
	EXPENSE_LEGAL,         // "Legal Fees"
	EXPENSE_MANUFACTURE,   // "Manufacturing"
	EXPENSE_CARS,          // "New Cars"
	EXPENSE_SHOPPING,      // "Purchasing Goods"
	EXPENSE_RECRUITMENT,   // "Recruitment"
	EXPENSE_RENT,          // "Rent"
	EXPENSE_COMPOUND,      // "Safehouse Investments"
	EXPENSE_TRAINING,      // "Training"
	EXPENSE_TRAVEL,        // "Travel"
	EXPENSE_TSHIRTS,       // "T-Shirt Materials"
	EXPENSETYPENUM         // # of types of expenses
};
