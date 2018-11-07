DROP TABLE IF EXISTS voronoi_cells;
CREATE TABLE voronoi_cells (
	osm_id BIGINT NOT NULL,
	sub_id INT NOT NULL,
	class INT
	/* PRIMARY KEY(osm_id, sub_id) */
);
SELECT AddGeometryColumn ('voronoi_cells','poly',4326,'LINESTRING',2);
