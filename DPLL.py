from sympy.logic.boolalg import And, Or, Not, Implies, Xor, to_cnf
import copy


class DPLL:
    def __init__(self, clauses, fixed_assignment):
        self.clauses = clauses
        self.fixed_assignment = fixed_assignment
        self.init_assignment()

    def init_assignment(self):
        self.assignment = {}
        for clause in self.clauses:
            for lit in clause:
                value = self.fixed_assignment.get(self.__get_lit_str(lit), -1)
                self.assignment[self.__get_lit_str(lit)] = value
 
    

    def __get_lit_str(self, lit):
        return str(lit) if lit.is_Symbol else str(Not(lit))


    def __assign(self, lit):
        value = True if lit.is_Symbol else False
        if lit in self.fixed_assignment and value != self.fixed_assignment.get(self.__get_lit_str(lit), None):
            return False
        elif self.__get_lit_str(lit) not in self.fixed_assignment or value == self.fixed_assignment.get(self.__get_lit_str(lit), None):
            self.assignment[self.__get_lit_str(lit)] = value
        return True


    def pure_literals_elimination(self, clauses):
        """
            Literal is pure when there is only one type (positive of negative) of literal
            We therefore assign the literal and remove all clauses that have this literal
        """
        literals = {lit for clause in clauses for lit in clause}
        pure_literals = {lit for lit in literals if Not(lit) not in literals}
        for lit in pure_literals:
            if not self.__assign(lit):
                return False, clauses
            clauses = [clause for clause in clauses if lit not in clause]
        return True, clauses


    def unit_clauses(self, clauses):
        unit_clauses= {clause for clause in clauses if len(clause) == 1}
        new_clauses = []
        for clause in unit_clauses:
            lit = clause[0]
            if not self.__assign(lit):
                return False, clauses
            new_clauses = [clause for clause in clauses if lit not in clause and Not(lit) not in clause]
            return True, new_clauses
        return True, clauses
    

    def get_lit(self, clauses):
        for clause in clauses:
            for lit in clause:
                if self.assignment.get(self.__get_lit_str(lit), -1) != -1:
                    return lit
    
    
    def run(self):

        if all(clause for clause in self.clauses) and not -1 in self.assignment.values():
            return True, self.assignment

        if any(len(clause) == 0 for clause in self.clauses):
            return False, self.assignment

        satisfiable, self.clauses = self.unit_clauses(self.clauses)
        if not satisfiable:
            return False, self.assignment
        
        satisfiable, self.clauses = self.pure_literals_elimination(self.clauses)

        literal = self.get_lit(self.clauses)
        if literal is None:
            return True, self.assignment

        if literal in fixed_assignments:
            result, new_assignment = dpll(clauses, self.assignment.copy(), fixed_assignments)
            if result:
                return True, new_assignment
            else:
                return False, self.assignment

         # Try assigning the literal to True
        self.assignment[self.__get_lit_str(literal)] = True
        result_true, new_assignment_true = dpll(self.clauses, self.assignment.copy(), self.fixed_assignments)
        if result_true:
            # Try assigning the literal to False
            self.assignment[self.__get_lit_str(literal)] = False
            result_false, new_assignment_false = dpll(self.clauses, self.assignment.copy(), self.fixed_assignments)
            if result_false:
                self.assignment[self.__get_lit_str(literal)] = "Undetermined"
            return True, new_assignment_true
        else:
            # Try assigning the literal to False
            self.assignment[self.__get_lit_str(literal)] = False
            return dpll(self.clauses, self.assignment.copy(), self.fixed_assignments)