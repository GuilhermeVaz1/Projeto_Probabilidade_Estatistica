CREATE TABLE IF NOT EXISTS hardware(
	id SERIAL PRIMARY KEY,
	cpu VARCHAR(100) NOT NULL,
	ram real NOT NULL
);

CREATE TABLE IF NOT EXISTS bubble_results(
	id SERIAL PRIMARY KEY,
	hardware_id INT,
	size INT NOT NULL,
	time1 INT NOT NULL,
	time2 INT NOT NULL,
	time3 INT NOT NULL,
	time4 INT NOT NULL,
	time5 INT NOT NULL,
	CONSTRAINT hardware_id FOREIGN KEY(hardware_id) REFERENCES hardware(id)
);

CREATE TABLE IF NOT EXISTS quick_results(
	id SERIAL PRIMARY KEY,
	hardware_id INT,
	size INT NOT NULL,
	time1 INT NOT NULL,
	time2 INT NOT NULL,
	time3 INT NOT NULL,
	time4 INT NOT NULL,
	time5 INT NOT NULL,
	CONSTRAINT hardware_id FOREIGN KEY(hardware_id) REFERENCES hardware(id)
);

CREATE TABLE IF NOT EXISTS merge_results(
	id SERIAL PRIMARY KEY,
	hardware_id INT,
	size INT NOT NULL,
	time1 INT NOT NULL,
	time2 INT NOT NULL,
	time3 INT NOT NULL,
	time4 INT NOT NULL,
	time5 INT NOT NULL,
	CONSTRAINT hardware_id FOREIGN KEY(hardware_id) REFERENCES hardware(id)
);

CREATE OR REPLACE FUNCTION
bubble(aaa int)
RETURNS TABLE (
	id int,
	hardware_id int,
	size int,
	time1 int,
	time2 int,
	time3 int,
	time4 int,
	time5 int
)
LANGUAGE plpgsql AS
$func$
BEGIN
	RETURN QUERY
	SELECT * FROM bubble_results WHERE bubble_results.hardware_id = aaa
	ORDER BY bubble_results.id;
END
$func$;

CREATE OR REPLACE FUNCTION
merge(aaa int)
RETURNS TABLE (
	id int,
	hardware_id int,
	size int,
	time1 int,
	time2 int,
	time3 int,
	time4 int,
	time5 int
)
LANGUAGE plpgsql AS
$func$
BEGIN
	RETURN QUERY
	SELECT * FROM merge_results WHERE merge_results.hardware_id = aaa
	ORDER BY merge_results.id;
END
$func$;

CREATE OR REPLACE FUNCTION
quick(aaa int)
RETURNS TABLE (
	id int,
	hardware_id int,
	size int,
	time1 int,
	time2 int,
	time3 int,
	time4 int,
	time5 int
)
LANGUAGE plpgsql AS
$func$
BEGIN
	RETURN QUERY
	SELECT * FROM quick_results WHERE quick_results.hardware_id = aaa
	ORDER BY quick_results.id;
END
$func$;