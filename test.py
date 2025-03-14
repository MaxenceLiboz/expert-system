from sympy.logic.boolalg import And, Or, Not, Implies, Xor, to_cnf
from sympy import symbols
from Converter import Converter

def get_lit_str(lit):
    if lit.is_Symbol :
        return str(lit)
    else:
        return str(Not(lit))


def set_assignement(assignment, lit):
    is_assigned = assignment.get(get_lit_str(lit), None)
    if lit.is_Symbol and is_assigned == None:
            assignment[str(lit)] = True
    elif is_assigned == None:
        assignment[str(Not(lit))] = False

def dpll(clauses, assignment={}):
    """
    DPLL algorithm for solving SAT problems.
    
    :param clauses: List of sets (CNF clauses)
    :param assignment: Current variable assignments
    :return: Boolean (SAT or UNSAT) and variable assignments if SAT
    """
    
    # Step 1: Check Base Cases
    if not clauses:  
        return True, assignment  # Satisfiable (no clauses left)
    if any(not clause for clause in clauses):  
        return False, None  # Unsatisfiable (empty clause exists)
    if all(clause for clause in clauses) and not None in assignment.values():
        return True, assignment
    
    # Step 2: Unit Propagation
    unit_literals = {list(clause)[0] for clause in clauses if len(clause) == 1}
    while unit_literals:
        literal = unit_literals.pop()
        if assignment.get(literal, None) == None or assignment.get(Not(literal), None) == None: 
            set_assignement(assignment, literal)
            clauses = [clause for clause in clauses if literal not in clause]  # Remove satisfied clauses
            for clause in clauses:
                clause.discard(-literal)  # Remove negation from remaining clauses
            unit_literals = {list(clause)[0] for clause in clauses if len(clause) == 1}

    # Step 3: Pure Literal Elimination
    literals = {lit for clause in clauses for lit in clause}
    pure_literals = {lit for lit in literals if Not(lit) not in literals}
    for lit in pure_literals:
        if not clauses or assignment.get(get_lit_str(lit), None) != None:
            continue
        set_assignement(assignment, lit)
        # clauses = [clause for clause in clauses if lit not in clause]

    # Step 4: Splitting (Backtracking)
    if not clauses:
        return True, assignment  # Satisfiable

    for first_literal in literals:
        if assignment.get(get_lit_str(first_literal), None) == None:
            valid_assignments = []  # Store valid results
            for value in [first_literal, Not(first_literal)]:  # Try True & None
                if assignment.get(get_lit_str(value), None) == None: 
                    new_assignment = assignment.copy()
                    set_assignement(new_assignment, value)

                    # Remove satisfied clauses, remove ¬value from remaining clauses
                    new_clauses = [clause.copy() for clause in clauses if value not in clause]
                    for clause in new_clauses:
                        clause.discard(Not(value))

                    result, final_assignment = dpll(new_clauses, new_assignment)
                    if result:
                        valid_assignments.append(value)  # Track valid values
            if len(valid_assignments) == 2:
                assignment[get_lit_str(first_literal)] = "UNDETERMINED"
            elif len(valid_assignments) == 1:
                assignment[get_lit_str(valid_assignments[0])] = True
            else:
                raise Exception("Contradiction occur")  # Contradiction
            return True, assignment
    

    return False, assignment  # Unsatisfiable


converter = Converter() 
cnf_clauses = converter.cnf_list(["A+B=>C", "A+B+C=>D", "C=>E"])
print(cnf_clauses)

# assignment = []
# for l in lit:
#     if l.is_Symbol:  # If it's a variable (e.g., A, B, C)
#         assignment[l] = True
#     else:  # If it's a negated variable (~A)
#         assignment[-l] = False

# print(assignment)


# Run DPLL
sat, assignment = dpll(cnf_clauses, {'a': True, 'b': True, 'c': None, 'd': None, 'e': None})
print(f"Satisfiable: {sat}")
print(f"Variable Assignments: {assignment}")
# if sat:
