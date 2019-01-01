INSERT INTO dijkstra_lines VALUES (1, 0, 1,
	ST_GeomFromText('LINESTRING(3.9 1.9, 6.8 1.2)', 4326)
);
INSERT INTO dijkstra_lines VALUES (1, 1, 1,
	ST_GeomFromText('LINESTRING(6.5 2.2, 9.2 4.1)', 4326)
);
INSERT INTO dijkstra_lines VALUES (1, 2, 1,
	ST_GeomFromText('LINESTRING(8.4 2.1, 9.3 1.0)', 4326)
);
INSERT INTO dijkstra_lines VALUES (1, 3, 1,
	ST_GeomFromText('LINESTRING(6.8 9.1, 9.6 6.2)', 4326)
);

INSERT INTO dijkstra_lines VALUES (2, 0, 2,
	ST_GeomFromText('LINESTRING(4.0 5.2, 5.9 5.4)', 4326)
);
INSERT INTO dijkstra_lines VALUES (2, 1, 2,
	ST_GeomFromText('LINESTRING(6.4 6.1, 7.3 4.7)', 4326)
);
INSERT INTO dijkstra_lines VALUES (2, 2, 2,
	ST_GeomFromText('LINESTRING(3.7 7.1, 7.8 7.1)', 4326)
);

INSERT INTO dijkstra_lines VALUES (3, 0, 3,
	ST_GeomFromText('LINESTRING(2.4 6.2, 2.8 8.5)', 4326)
);
INSERT INTO dijkstra_lines VALUES (3, 1, 3,
	ST_GeomFromText('LINESTRING(2.0 5.0, 3.7 5.8)', 4326)
);
INSERT INTO dijkstra_lines VALUES (3, 2, 3,
	ST_GeomFromText('LINESTRING(3.0 4.5, 5.6 3.3)', 4326)
);

/* BOUNDING BOX */

INSERT INTO dijkstra_lines VALUES (999, 0, 999,
	ST_GeomFromText('LINESTRING(-100 -100, -100 100)', 4326)
);
INSERT INTO dijkstra_lines VALUES (999, 1, 999,
	ST_GeomFromText('LINESTRING(-100 -100, 100 -100)', 4326)
);
INSERT INTO dijkstra_lines VALUES (999, 0, 999,
	ST_GeomFromText('LINESTRING(100 100, -100 100)', 4326)
);
INSERT INTO dijkstra_lines VALUES (999, 0, 999,
	ST_GeomFromText('LINESTRING(100 100, 100 -100)', 4326)
);
