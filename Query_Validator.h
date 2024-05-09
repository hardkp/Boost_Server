#pragma once
#include "Interface.h"

class Query_Validator :  public Validator<std::string>{
private:

public:

	bool to_validate(std::string query) override;

};

