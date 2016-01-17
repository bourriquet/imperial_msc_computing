% part of the solution to tut2 Q4
function [score] = activity_scores(A)
    score = ((1/48).*A.data(:,3)) + ((4/48).*A.data(:,4)) + ((20/48).*A.data(:,5))
end
