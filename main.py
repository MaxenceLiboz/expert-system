
from Converter import Converter
# from DPLL import DPLL
from sympy.logic.boolalg import And, Or, Not, Implies, Xor, to_cnf
from sympy import simplify

# dpll = DPLL(cnf_clauses, {'a': True, 'd': False})
# sat, assignment = dpll.run()
# print(f"Satisfiable: {sat}")
# print(f"Variable Assignments: {assignment}")


def is_pure(literal, clauses):
    all_literals = {lit for clause in clauses for lit in clause}
    is_pure = True if Not(literal) not in all_literals else False

def choose_literal(clauses):
    for clause in clauses:
        for lit in clause:
            return lit

def propagate(clauses, literal):
    new_clauses = []
    for clause in clauses:
        if literal in clause:
            continue  # Clause is satisfied, skip it
        if Not(literal) in clause:
            clause.remove(Not(literal))  # Simplify the clause
        if not clause:
            return []  # Empty clause means contradiction
        new_clauses.append(clause)
    return new_clauses


def dpll(clauses, assignment):

    new_clauses = []
    for clause in clauses:
        for literal in assignment:
            if literal in clause or Not(literal) in clause:
                if assignment[literal] == True:
                    clause.remove(Not(literal))
                elif assignment[literal] == False:
                    clause.remove(literal)
        new_clauses.append(clause)
    clauses = new_clauses

    unit_clauses = [clause for clause in clauses if len(clause) == 1]
    new_clauses = []
    for clause in unit_clauses:
        lit = next(iter(clause))
        assignment[str(lit) if lit.is_Symbol else str(Not(lit))] = True if lit.is_Symbol else False

    clauses = [clause for clause in clauses if clause not in unit_clauses]
    print(clause)
            
    

converter = Converter() 
cnf_clauses = converter.cnf_list(["A+B=>C", "A+B+C=>D", "C=>E"])
print(cnf_clauses)

sat, assignment = dpll(cnf_clauses, {'a': True, 'b': True})

print("FIN")