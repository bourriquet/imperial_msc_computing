% the students in Hogwarts
student(hp, 'Harry James Potter', gryffindor).
student(hg, 'Hermione Jean Granger', gryffindor).
student(rw, 'Ronald Weasley', gryffindor).
student(ll, 'Luna Lovegood', ravenclaw).
student(cc, 'Cho Chang', ravenclaw).
student(tb, 'Terry Boot', ravenclaw).
student(ha, 'Hannah Abbott', hufflepuff).
student(cd, 'Cedric Diggory', hufflepuff).
student(nt, 'Nymphadora Tonks',hufflepuff).
student(dm, 'Draco Malfoy', slytherin).
student(gg, 'Gregory Goyle', slytherin).
student(vc, 'Vincent Crabbe', slytherin).

% the teachers in Hogwarts
teacher(ad, 'Albus Percival Wulfric Brian Dumbledore').
teacher(ff, 'Filius Flitwick').
teacher(rh, 'Rubeus Hagrid').
teacher(gl, 'Gilderoy Lockhart').
teacher(rl, 'Remus John Lupin').
teacher(mm, 'Minerva McGonagall').
teacher(qq, 'Quirinus Quirrell').
teacher(ss, 'Severus Snape').
teacher(ps, 'Pomona Sprout').
teacher(st, 'Sibyll Patricia Trelawney').
teacher(mh, 'Madam Hooch').
teacher(as, 'Aurora Sinistra').
teacher(cub, 'Cuthbert Binns').
teacher(bb, 'Bathsheba Babbling').
teacher(sv, 'Septima Vector').
teacher(chb, 'Charity Burbage').
teacher(wt, 'Wilkie Twycross').

% compulsory courses for the MSc in Magic
compCourse(astro, 'Astronomy', as).
compCourse(charms, 'Charms', ff).
compCourse(defence, 'Defence against the Dark Arts', qq).
compCourse(fly, 'Flying', mh).
compCourse(herb, 'Herbology', ps).
compCourse(history, 'History of Magic', cub).
compCourse(potions, 'Potions', ss).
compCourse(trans, 'Transfiguration', mm).

% optional courses for the MSc in Magic
optCourse(runes, 'Study of Ancient Runes', bb).
optCourse(arith, 'Arithmancy', sv).
optCourse(muggle, 'Muggle Studies', chb).
optCourse(creatures, 'Care of Magical Creatures', rh).
optCourse(div, 'Divination', st).
optCourse(app, 'Apparition', wt).
optCourse(choir, 'Frog Choir', ff).
optCourse(quid, 'Quidditch', mh).




%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 1               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

student(la, 'Lauren Anders', ravenclaw).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 2               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/* students' optional course choices */

enrolled_opt(hp, arith).
enrolled_opt(hp, quid).
enrolled_opt(hp, div).

enrolled_opt(hg, runes).
enrolled_opt(hg, div).
enrolled_opt(hg, muggle).
enrolled_opt(hg, creatures).
enrolled_opt(hg, arith).
enrolled_opt(hg, app).

enrolled_opt(rw, quid).
enrolled_opt(rw, runes).
enrolled_opt(rw, div).

enrolled_opt(ll, creatures).
enrolled_opt(ll, div).
enrolled_opt(ll, runes).

enrolled_opt(cc, creatures).
enrolled_opt(cc, div).
enrolled_opt(cc, quid).

enrolled_opt(tb, runes).
enrolled_opt(tb, muggle).
enrolled_opt(tb, app).

enrolled_opt(ha, runes).
enrolled_opt(ha, arith).
enrolled_opt(ha, creatures).

enrolled_opt(cd, quid).
enrolled_opt(cd, muggle).
enrolled_opt(cd, div).

enrolled_opt(nt, runes).
enrolled_opt(nt, arith).
enrolled_opt(nt, creatures).

enrolled_opt(dm, quid).
enrolled_opt(dm, arith).
enrolled_opt(dm, app).

enrolled_opt(gg, runes).
enrolled_opt(gg, div).
enrolled_opt(gg, arith).

enrolled_opt(vc, muggle).
enrolled_opt(vc, arith).
enrolled_opt(vc, creatures).

enrolled_opt(la, arith).
enrolled_opt(la, quid).
enrolled_opt(la, div).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 3               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/* 
enrolled(?SID, ?SCN) :-
   student with an ID of SID is enrolled on the course with
   short name SCN (compulsory or optional)
      
   SCN is either a compulsory course, or it is optional and
   the student is enrolled on it
*/

enrolled(SID, SCN) :-
    student(SID, _, _),
    (compCourse(SCN, _, _); enrolled_opt(SID, SCN)).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 4               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
teaches(?TN, ?SCN) :-
   the wizard/witch with name TN teaches the course with short
   name SCN
*/

teaches(TN, SCN) :-
    teacher(TID, TN),
    (compCourse(SCN, _, TID); optCourse(SCN, _, TID)).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 5               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
taughtBy(?SN, ?TN) :-
   the student with name SN is enrolled on a course that is
   taught by the teacher with name TN
*/

taughtBy(SN, TN) :-
    student(SID, SN, _),
    enrolled(SID, SCN),
    teaches(TN, SCN).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 6               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
takesOption(?SN, ?CN) :-
   the student with name SN is enrolled on the optional course
   with name CN
*/

takesOption(SN, CN) :-
    student(SID, SN, _),
    optCourse(SCN, CN, _),
    enrolled_opt(SID, SCN).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 7               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
takesAllOptions(?SN, ?OptCourses) :-
   OptCourses is the list of optional courses (in alphabetical
   order) that the student with name SN has chosen
*/

takesAllOptions(SN, OptCourses) :-
    setof(CN, takesOption(SN, CN), OptCourses).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 8               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
studentsInHouse(?House, ?Students) :-
   Students is a list of SN which are in House, ordered
   alphabetically by SID

   get a set of IDs first, then findall names that are a member
   of the list of IDs (Students will then be ordered by name)
*/

studentsInHouse(House, Students) :-
    setof(SID, SN^student(SID, SN, House), StudentIDs),
    findall(SN, (member(SID, StudentIDs), student(SID, SN, House)), Students).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 9               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
studentsOnCourse(?SCN, ?CN, ?StudentsByHouse) :-
   for a course with short name SCN and name CN,
   StudentsByHouse is a list of 4 elements of the form
   House-Students, where Students is listed by name


HELPER PREDICATE:

enrolledHouse(House, SCN, List) :-
   List is a list of the names of students in House, enrolled
   on the course with short name SCN
*/

studentsOnCourse(SCN, CN, [gryffindor-GryffindorList, hufflepuff-
HufflepuffList, ravenclaw-RavenclawList, slytherin-SlytherinList]) :-
   (compCourse(SCN, CN, _); optCourse(SCN, CN, _)),
   enrolledHouse(gryffindor, SCN, GryffindorList),
   enrolledHouse(ravenclaw, SCN, RavenclawList),
   enrolledHouse(hufflepuff, SCN, HufflepuffList),
   enrolledHouse(slytherin, SCN, SlytherinList).

enrolledHouse(House, SCN, List) :-
   findall(SN, (student(SID, SN, House), enrolled(SID, SCN)), List).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 10              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
sharedCourse(?SN1, ?SN2, ?CN) :-
   optional course with name CN is taken by two different
   students with names SN1 and SN2
*/

sharedCourse(SN1, SN2, CN) :-
    takesOption(SN1, CN),
    takesOption(SN2, CN),
    SN1 \= SN2.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% QUESTION 11              %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
sameOptions(?SN1, ?SN2, ?Courses) :-
   two different students with names SN1 and SN2 are
   enrolled on exactly the same three courses forming
   the list Courses

   if the student is Hermione, she has the same courses
   as another student if 3 out of her 6 courses match

   (can probably be more concise)


HELPER PREDICATE:

checkCourses(List1, List2) :-
   checks if all elements of List1 are elements of List2
*/

sameOptions(SN1, SN2, Courses) :-
    (student(_, SN1, _), student(_, SN2, _)),
    (SN1 \= 'Hermione Jean Granger', SN2 \= 'Hermione Jean Granger'),
    SN1 \= SN2,
    takesAllOptions(SN1, Courses),
    takesAllOptions(SN2, Courses2),
    checkCourses(Courses, Courses2).

sameOptions(SN1, SN2, Courses) :-
    (student(_, SN1, _), student(_, SN2, _)),
    SN1 \= SN2,
    ((SN1 = 'Hermione Jean Granger',
    takesAllOptions(SN2, Courses),
    takesAllOptions(SN1, Courses2),
    checkCourses(Courses, Courses2));
    (SN2 = 'Hermione Jean Granger', 
    takesAllOptions(SN1, Courses),
    takesAllOptions(SN2, Courses2),
    checkCourses(Courses, Courses2))).

checkCourses([], []).
checkCourses([], [_|_]).
checkCourses([H|T], List) :-
    member(H, List),
    checkCourses(T, List).
