DROP TABLE IF EXISTS dijkstra_lines;
CREATE TABLE dijkstra_lines (
	osm_id BIGINT NOT NULL,
	sub_id INT NOT NULL,
	class INT
	/* PRIMARY KEY(osm_id, sub_id) */
);
SELECT AddGeometryColumn ('dijkstra_lines','line',4326,'LINESTRING',2);

DROP TABLE IF EXISTS dijkstra_lines_2;
CREATE TABLE dijkstra_lines_2 (
         osm_id BIGINT NOT NULL,
         sub_id INT NOT NULL,
         class INT
         /* PRIMARY KEY(osm_id, sub_id */
);
SELECT AddGeometryColumn ('dijkstra_lines_2','line',4326,'LINESTRING',2);
