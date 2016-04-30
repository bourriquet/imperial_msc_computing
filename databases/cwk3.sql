/*
Author: lc3311
Last updated: 24/02/16
*/

-- Q1 returns (first_name)

/*
The first name is either the substring before a ' ' in name, or the entire name

If there is a ' ' in name (found using LIKE), create a substring containing the first name
*/

SELECT DISTINCT
	CASE
		WHEN name LIKE '% %' THEN SUBSTRING(name FROM 1 FOR POSITION(' ' IN name)-1)
		ELSE name
	END
	AS first_name
FROM person
ORDER BY first_name ASC
;

-- Q2 returns (born_in, popularity)

/*
GROUP BY location and count the occurrences of each location
*/

SELECT born_in,
COUNT(born_in) AS popularity
FROM person
GROUP BY born_in
ORDER BY popularity DESC, born_in ASC
;

-- Q3 returns (house, seventeenth, eighteenth, nineteenth, twentieth)

/*
Perform a count for each century
*/

SELECT house,
	COUNT
		(CASE 
		WHEN EXTRACT(year FROM accession) >= 1600 
		AND EXTRACT(year FROM accession) < 1700
		THEN accession 
		ELSE NULL
		END) 
	as seventeenth,
        COUNT
                (CASE
                WHEN EXTRACT(year FROM accession) >= 1700
                AND EXTRACT(year FROM accession) < 1800
                THEN accession
                ELSE NULL
                END)
        as eighteenth,
        COUNT
                (CASE
                WHEN EXTRACT(year FROM accession) >= 1800
                AND EXTRACT(year FROM accession) < 1900
                THEN accession
                ELSE NULL
                END)
        as nineteenth,
        COUNT
                (CASE
                WHEN EXTRACT(year FROM accession) >= 1900
                AND EXTRACT(year FROM accession) < 2000
                THEN accession
                ELSE NULL
                END)
        as twentieth
FROM monarch
WHERE house IS NOT NULL
GROUP BY house
ORDER BY house
;

-- Q4 returns (name, age)

/*
Find the minimum dob (first born) for each parent (union of father and mother),
then select the name and compute the age from this

This method doesn't take leap years into account
*/

SELECT name, ((first_born.dob - person.dob)/365) AS age
FROM person, (SELECT MIN(dob) AS dob, mother AS parent
		FROM person
		WHERE mother IS NOT NULL
		GROUP BY mother
		UNION
		SELECT MIN(dob) AS dob, father AS parent
		FROM person
		WHERE father IS NOT NULL
		GROUP BY father) first_born
WHERE name = first_born.parent
ORDER BY name
;

-- Q5 returns (father, child, born)

/*
Left join person containing only fathers with their children ranked in order
of birth, to person to get a table with all males and their children (if
applicable) ranked in order of birth
*/

SELECT person.name AS father, rankings.name as child, born
FROM person
LEFT JOIN (SELECT father, name, dob,
		RANK() OVER (PARTITION BY father ORDER BY dob ASC) AS born
		FROM person
		WHERE father IS NOT NULL) rankings ON person.name = rankings.father
WHERE gender = 'M'
ORDER BY father ASC, born ASC
;

-- Q6 returns (monarch, prime_minister)

/*
Create a temporary table for the PMs and their entry and exit dates, and a
temporary table for the monarchs and their accession and exit dates

Then select the monarchs and PMs that satisfy the following conditions:
- the monarch is still ruling and their accession predates the PM's entry
- the monarch is still ruling and their accession predates the PM's exit
- the PM's entry is after the monarch's accession and before the monarch's exit
- the PM's exit is after the monarch's accession and before the monarch's exit
- the monarch's accession is before the PM's entry and their exit is after the PM's exit
- the PM's entry is before the monarch's accession and after the monarch's exit
*/

CREATE TEMP TABLE pm_dates AS
SELECT pm_a.name AS name, pm_a.entry, pm_b.entry AS exit
FROM prime_minister AS pm_a
LEFT JOIN prime_minister AS pm_b ON pm_b.entry > pm_a.entry
WHERE pm_b.entry <= ALL (SELECT pm_c.entry
				FROM prime_minister AS pm_c
				WHERE pm_c.entry > pm_a.entry)
;

CREATE TEMP TABLE monarch_dates AS
SELECT monarch_a.name AS name, monarch_a.accession, monarch_b.accession AS exit
FROM monarch as monarch_a
LEFT JOIN monarch AS monarch_b ON monarch_b.accession > monarch_a.accession
WHERE monarch_b.accession <= ALL (SELECT monarch_c.accession
					FROM monarch AS monarch_c
					WHERE monarch_c.accession > monarch_a.accession)
;

SELECT DISTINCT monarch_dates.name AS monarch, pm_dates.name AS prime_minister
FROM monarch_dates, pm_dates
WHERE (monarch_dates.exit IS NULL AND monarch_dates.accession < pm_dates.entry)
OR (monarch_dates.exit IS NULL AND monarch_dates.accession < pm_dates.exit)
OR (pm_dates.entry > monarch_dates.accession AND pm_dates.entry < monarch_dates.exit)
OR (pm_dates.exit > monarch_dates.accession AND pm_dates.exit < monarch_dates.exit)
OR (monarch_dates.accession < pm_dates.entry AND monarch_dates.exit > pm_dates.exit)
OR (pm_dates.entry < monarch_dates.accession AND pm_dates.entry > monarch_dates.exit)
ORDER BY monarch ASC, prime_minister ASC
;
