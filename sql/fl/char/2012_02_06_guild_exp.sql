ALTER TABLE `guild_member` ADD COLUMN `m_today_xp` bigint(20) NOT NULL AFTER `level`;
ALTER TABLE `guild_member` ADD COLUMN `m_xp_cap` bigint(20) NOT NULL AFTER `m_today_xp`;