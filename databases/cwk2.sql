/*

Author: lc3311
Last updated: 13/02/16

*/

-- Q1 returns (name,name,born_in)

/*
This RA query returns the names of two people if they had a child
together and were born in the same place

As the pi operator returns a set, SELECT DISTINCT is required

INNER JOIN the person table to itself twice under different aliases,
so that the born_in attribute of the mother (person_b) and father
(person_a) can be compared

No need to check for nulls, as the father and mother attributes
won't be joined if they're null. The born_in attribute can't be null
*/

SELECT DISTINCT person_a.name, person_b.name, person_a.born_in
FROM person AS person_c
INNER JOIN person AS person_a ON person_a.name = person_c.father
INNER JOIN person AS person_b ON person_b.name = person_c.mother
WHERE person_a.born_in = person_b.born_in
;

-- Q2 returns (name)

/*
If house is null, then the monarch was not a King or Queen, so we
do not want these rows

If coronation is null, the King/Queen was not coronated
*/

SELECT name 
FROM monarch
WHERE house IS NOT NULL
AND coronation IS NULL
ORDER BY name ASC
;

-- Q3 returns (name,father,mother)

/*
INNER JOIN the person table to itself twice under different aliases,
so that the dod attributes can be compared

The following scenarios need to be captured:
- the person died before both of their parents, who have also died
- the person died before one of their parents, and the other is still alive
- the person has died and both parents are still alive
As the dod is null if a person died (and the join is not performed
over the dod attribute), the IS NOT FALSE condition over
(person.dod < parent.dod) can be used to find all of the above
scenarios. However, we must also check that the person's dod is not
null, as comparing this null dod value would result in the IS NOT FALSE
condition returning true, even though the person has not died
*/

SELECT person.name, person.father, person.mother
FROM person
INNER JOIN person AS person_a ON person_a.name = person.father
INNER JOIN person AS person_b ON person_b.name = person.mother
WHERE person.dod IS NOT NULL
AND (person.dod < person_a.dod) IS NOT FALSE
AND (person.dod < person_b.dod) IS NOT FALSE
ORDER BY person.name ASC
;

-- Q4 returns (name)

/*
To list all people that have been either a King, Queen OR PM,
a UNION is needed between 

If house is null, then the monarch was not a King or Queen, so we
do not want these rows
*/

(SELECT name
FROM monarch
WHERE monarch.house IS NOT NULL)
UNION
(SELECT name
FROM prime_minister)
ORDER BY name ASC
;

-- Q5 returns (name)

/*
This query uses an EXCEPT between a query that returns all Kings
and Queens that have died, and a query that returns all Kings
and Queens that acceded to the throne on the same date that
another King and Queen died

Only need to check that the house and dod attributes are not
null in the first query
*/

(SELECT person.name
FROM person
INNER JOIN monarch ON person.name = monarch.name
WHERE house IS NOT NULL
AND dod IS NOT NULL)
EXCEPT
(SELECT person.name
FROM person
INNER JOIN monarch ON person.dod = monarch.accession)
ORDER BY name ASC
;

-- Q6 returns (house,name,accession)

/*
First project the house, name and accession of all monarchs.
Here, I have assumed that 'first of a house' means that the
house attribute cannot be null

Then, return all the rows where the accession is less than
all accessions in the sub-query

The sub-query finds all accessions of monarchs of the same house
as the monarch being compared, where the monarch does not have
the same name (i.e. is a different monarch) to the one whose
accession is being compared

As two monarchs can accede to the throne on the same date (e.g.
a King and Queen), I have chosen the comparison operator to be '<='
*/

SELECT house, name, accession
FROM monarch
WHERE house IS NOT NULL
AND accession <= ALL (SELECT accession
			FROM monarch AS monarch2
			WHERE monarch2.name <> monarch.name
			AND monarch2.house = monarch.house)
ORDER BY accession ASC
;

