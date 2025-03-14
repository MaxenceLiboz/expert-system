import re
from sympy.logic.boolalg import And, Or, Not, Implies, Xor, to_cnf
from sympy.abc import symbols
from sympy import simplify
from copy import copy

class Converter:
    def __init__(self):
        return


    def to_cnf(self, expr):
        before_expr = copy(expr)
        expr = self.__sanitize_expr(expr)
        cnf_expr = to_cnf(expr.lower(), True)

        return {"before_expr": before_expr, "expr": expr, "cnf_expr": cnf_expr}

    
    def cnf_list(self, exprs):
        cnf_clauses = []
        for expr in exprs:
            cnf_expr = self.to_cnf(expr).get("cnf_expr")
            cnf_clauses += self.__cnf_for_dpll(cnf_expr)
        return cnf_clauses
            

    def __cnf_for_dpll(self, expr):
        cnf_clauses = []
        if expr.func == And:  # If multiple clauses, unpack
            cnf_clauses.extend([{lit for lit in sub_clause.args} if sub_clause.func == Or else {sub_clause} for sub_clause in expr.args])
        else:  # Single clause
            cnf_clauses.append({lit for lit in expr.args} if expr.func == Or else {expr})
        return cnf_clauses


    def __sanitize_expr(self, expr):
        """Sanitize the expr in order to fit sympy requirement"""

        expr = expr.replace(" ", "")
        expr = expr.replace("+", "&")
        expr = expr.replace("!", "~")

        if expr.find("^") != -1:
            # Replace A ^ B with (A | B) & (!A | !B)
            biimplication_pattern = r'(.{0,1})\s*\^\s*(.{0,1})'  
            biimplication_replacement = r'(\1|\2)&(~\1|~\2)'
            expr = re.sub(biimplication_pattern, biimplication_replacement, expr)
        if expr.find("<=>") != -1:
            # Replace A ⇔ B with (A => B) & (B => A)
            biimplication_pattern = r'(.*?)\s*<=>\s*(.*)$'
            biimplication_replacement = r'((\1)>>(\2))&((\2)>>(\1))'
            expr = re.sub(biimplication_pattern, biimplication_replacement, expr)
        if expr.find("=>") != -1:
            # Replace A => B with (A) >> (B)
            biimplication_pattern = r'(.*?)\s*=>\s*(.*)$'
            biimplication_replacement = r'(\1)>>(\2)'
            expr = re.sub(biimplication_pattern, biimplication_replacement, expr)
        return expr
