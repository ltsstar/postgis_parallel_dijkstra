DROP TABLE IF EXISTS dijkstra_lines;
CREATE TABLE dijkstra_lines (
	osm_id BIGINT NOT NULL,
	sub_id INT NOT NULL,
	class INT
	/* PRIMARY KEY(osm_id, sub_id) */
);
SELECT AddGeometryColumn ('dijkstra_lines','line',4326,'LINESTRING',2);
