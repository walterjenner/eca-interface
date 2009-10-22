 SELECT artwork.artwork_id
FROM artwork
LEFT JOIN compartdb_creating ON artwork.artwork_id = compartdb_creating.artwork_id
LEFT JOIN agent ON compartdb_creating.agent_id = agent.agent_id
WHERE agent.agent_id =13
LIMIT 0 , 30 