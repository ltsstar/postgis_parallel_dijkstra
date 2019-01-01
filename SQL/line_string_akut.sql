DROP TABLE IF EXISTS dijkstra_lines_akut;
CREATE TABLE dijkstra_lines_akut (
	osm_id BIGINT NOT NULL,
	sub_id INT NOT NULL,
	class INT
	/* PRIMARY KEY(osm_id, sub_id) */
);
SELECT AddGeometryColumn ('dijkstra_lines_akut','line',4326,'LINESTRING',2);
