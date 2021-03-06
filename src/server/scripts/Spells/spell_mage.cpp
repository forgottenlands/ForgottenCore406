/*
 * Copyright (C) 2010 - 2012 ProjectSkyfire <http://www.projectskyfire.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2008 - 2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "ScriptPCH.h"

enum MageSpells {
	SPELL_MAGE_COLD_SNAP = 11958,
	SPELL_MAGE_GLYPH_OF_ETERNAL_WATER = 70937,
	SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT = 70908,
	SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY = 70907,
	SPELL_MAGE_GLYPH_OF_BLAST_WAVE = 62126
};

class spell_mage_cold_snap: public SpellScriptLoader {
public:
	spell_mage_cold_snap() :
			SpellScriptLoader("spell_mage_cold_snap") {
	}

	class spell_mage_cold_snap_SpellScript: public SpellScript {
		PrepareSpellScript(spell_mage_cold_snap_SpellScript)
		void HandleDummy(SpellEffIndex /*effIndex*/) {
			Unit *caster = GetCaster();

			if (caster->GetTypeId() != TYPEID_PLAYER)
				return;

			// immediately finishes the cooldown on Frost spells
			const SpellCooldowns& cm =
					caster->ToPlayer()->GetSpellCooldownMap();
			for (SpellCooldowns::const_iterator itr = cm.begin();
					itr != cm.end();) {
				SpellEntry const *spellInfo = sSpellStore.LookupEntry(
						itr->first);

				if (spellInfo->SpellFamilyName == SPELLFAMILY_MAGE
						&& (GetSpellSchoolMask(spellInfo)
								& SPELL_SCHOOL_MASK_FROST)
						&& spellInfo->Id != SPELL_MAGE_COLD_SNAP
						&& GetSpellRecoveryTime(spellInfo) > 0) {
					caster->ToPlayer()->RemoveSpellCooldown((itr++)->first,
							true);
				} else
					++itr;
			}
		}

		void Register() {
			// add dummy effect spell handler to Cold Snap
			OnEffect +=
					SpellEffectFn(spell_mage_cold_snap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_mage_cold_snap_SpellScript();
	}
};

class spell_mage_polymorph_cast_visual: public SpellScriptLoader 
{
public:
	spell_mage_polymorph_cast_visual() : SpellScriptLoader("spell_mage_polymorph_visual") 
    { }

	class spell_mage_polymorph_cast_visual_SpellScript: public SpellScript 
    {
		PrepareSpellScript(spell_mage_polymorph_cast_visual_SpellScript)

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
			if (Unit *unitTarget = GetHitUnit())
            {
                // Glyph of Polymorph
                if (GetCaster()->HasAura(56375))
                {
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, unitTarget->GetAura(32409)); // SW:D shall not be removed.
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                }
            }

		}

		void Register()
        {
			OnEffect += SpellEffectFn(spell_mage_polymorph_cast_visual_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
		}
	};

	SpellScript* GetSpellScript() const 
    {
		return new spell_mage_polymorph_cast_visual_SpellScript();
	}
};

// Frost Warding
class spell_mage_frost_warding_trigger: public SpellScriptLoader {
public:
	spell_mage_frost_warding_trigger() :
			SpellScriptLoader("spell_mage_frost_warding_trigger") {
	}

	class spell_mage_frost_warding_trigger_AuraScript: public AuraScript {
		PrepareAuraScript(spell_mage_frost_warding_trigger_AuraScript)
		;

		enum Spells {
			SPELL_MAGE_FROST_WARDING_TRIGGERED = 57776,
			SPELL_MAGE_FROST_WARDING_R1 = 28332,
		};

		bool Validate(SpellEntry const * /*spellEntry*/) {
			return sSpellStore.LookupEntry(SPELL_MAGE_FROST_WARDING_TRIGGERED)
					&& sSpellStore.LookupEntry(SPELL_MAGE_FROST_WARDING_R1);
		}

		void Absorb(AuraEffect * aurEff, DamageInfo & dmgInfo,
				uint32 & absorbAmount) {
			Unit * target = GetTarget();
			if (AuraEffect * talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_FROST_WARDING_R1, EFFECT_0)) {
				int32 chance = SpellMgr::CalculateSpellEffectAmount(
						talentAurEff->GetSpellProto(), EFFECT_1);

				if (roll_chance_i(chance)) {
					absorbAmount = dmgInfo.GetDamage();
					int32 bp = absorbAmount;
					target->CastCustomSpell(target,
							SPELL_MAGE_FROST_WARDING_TRIGGERED, &bp, NULL, NULL,
							true, NULL, aurEff);
				}
			}
		}

		void Register() {
			OnEffectAbsorb +=
					AuraEffectAbsorbFn(spell_mage_frost_warding_trigger_AuraScript::Absorb, EFFECT_0);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_mage_frost_warding_trigger_AuraScript();
	}
};

// Incanter's Absorption
class spell_mage_incanters_absorbtion_absorb: public SpellScriptLoader {
public:
	spell_mage_incanters_absorbtion_absorb() :
			SpellScriptLoader("spell_mage_incanters_absorbtion_absorb") {
	}

	class spell_mage_incanters_absorbtion_absorb_AuraScript: public AuraScript {
		PrepareAuraScript(spell_mage_incanters_absorbtion_absorb_AuraScript)
		;

		enum Spells {
			SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED = 44413,
			SPELL_MAGE_INCANTERS_ABSORBTION_R1 = 44394,
		};

		bool Validate(SpellEntry const * /*spellEntry*/) {
			return sSpellStore.LookupEntry(
					SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED)
					&& sSpellStore.LookupEntry(
							SPELL_MAGE_INCANTERS_ABSORBTION_R1);
		}

		void Trigger(AuraEffect * aurEff, DamageInfo & dmgInfo,
				uint32 & absorbAmount) {
			Unit * target = GetTarget();

			if (AuraEffect * talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_INCANTERS_ABSORBTION_R1, EFFECT_0)) {
				int32 bp = CalculatePctN(absorbAmount,
						talentAurEff->GetAmount());
				target->CastCustomSpell(target,
						SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL,
						NULL, true, NULL, aurEff);
			}
		}

		void Register() {
			AfterEffectAbsorb +=
					AuraEffectAbsorbFn(spell_mage_incanters_absorbtion_absorb_AuraScript::Trigger, EFFECT_0);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_mage_incanters_absorbtion_absorb_AuraScript();
	}
};

// Incanter's Absorption
class spell_mage_incanters_absorbtion_manashield: public SpellScriptLoader {
public:
	spell_mage_incanters_absorbtion_manashield() :
			SpellScriptLoader("spell_mage_incanters_absorbtion_manashield") {
	}

	class spell_mage_incanters_absorbtion_manashield_AuraScript: public AuraScript {
		PrepareAuraScript(spell_mage_incanters_absorbtion_manashield_AuraScript)
		;

		enum Spells {
			SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED = 44413,
			SPELL_MAGE_INCANTERS_ABSORBTION_R1 = 44394,
		};

		bool Validate(SpellEntry const * /*spellEntry*/) {
			return sSpellStore.LookupEntry(
					SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED)
					&& sSpellStore.LookupEntry(
							SPELL_MAGE_INCANTERS_ABSORBTION_R1);
		}

		void Trigger(AuraEffect * aurEff, DamageInfo & dmgInfo,
				uint32 & absorbAmount) {
			Unit * target = GetTarget();

			if (AuraEffect * talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_INCANTERS_ABSORBTION_R1, EFFECT_0)) {
				int32 bp = CalculatePctN(absorbAmount,
						talentAurEff->GetAmount());
				target->CastCustomSpell(target,
						SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL,
						NULL, true, NULL, aurEff);
			}
		}

		void Register() {
			AfterEffectManaShield +=
					AuraEffectManaShieldFn(spell_mage_incanters_absorbtion_manashield_AuraScript::Trigger, EFFECT_0);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_mage_incanters_absorbtion_manashield_AuraScript();
	}
};

class spell_mage_blast_wave : public SpellScriptLoader
{
    public:
        spell_mage_blast_wave() : SpellScriptLoader("spell_mage_blast_wave") { }

        class spell_mage_blast_wave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_blast_wave_SpellScript)
            bool Validate(SpellEntry const* /*spellEntry*/)
            {
                if (!sSpellStore.LookupEntry(SPELL_MAGE_GLYPH_OF_BLAST_WAVE))
                    return false;
                return true;
            }

            void HandleKnockBack(SpellEffIndex effIndex)
            {
                if (GetCaster()->HasAura(SPELL_MAGE_GLYPH_OF_BLAST_WAVE))
                    PreventHitDefaultEffect(effIndex);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_mage_blast_wave_SpellScript::HandleKnockBack, EFFECT_2, SPELL_EFFECT_KNOCK_BACK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_blast_wave_SpellScript();
        }
};

class spell_mage_summon_water_elemental : public SpellScriptLoader
{
    public:
        spell_mage_summon_water_elemental() : SpellScriptLoader("spell_mage_summon_water_elemental") { }

        class spell_mage_summon_water_elemental_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_summon_water_elemental_SpellScript)
            bool Validate(SpellEntry const* /*spellEntry*/)
            {
                if (!sSpellStore.LookupEntry(SPELL_MAGE_GLYPH_OF_ETERNAL_WATER))
                    return false;
                if (!sSpellStore.LookupEntry(SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY))
                    return false;
                if (!sSpellStore.LookupEntry(SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                // Glyph of Eternal Water
                if (caster->HasAura(SPELL_MAGE_GLYPH_OF_ETERNAL_WATER))
                    caster->CastSpell(caster, SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT, true);
                else
                    caster->CastSpell(caster, SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY, true);
            }

            void Register()
            {
                // add dummy effect spell handler to Summon Water Elemental
                OnEffectHit += SpellEffectFn(spell_mage_summon_water_elemental_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_summon_water_elemental_SpellScript();
        }
};

// cauterize
class spell_mage_cauterize : public SpellScriptLoader 
{
public:
    spell_mage_cauterize() : SpellScriptLoader("spell_mage_cauterize") 
    { }

    class spell_mage_cauterize_AuraScript: public AuraScript 
    {
        PrepareAuraScript(spell_mage_cauterize_AuraScript);

        uint32 healPct;

        enum Spell
        {
            MAGE_SPELL_CAUTERIZE_HEAL = 87023,
        };

        bool Validate(SpellEntry const * /*spellEntry*/) 
        {
            return sSpellStore.LookupEntry(MAGE_SPELL_CAUTERIZE_HEAL);
        }

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & canBeRecalculated) 
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect * aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * target = GetTarget();
            if (dmgInfo.GetDamage() < target->GetHealth())
                return;

            if (target->ToPlayer() && target->ToPlayer()->HasSpellCooldown(MAGE_SPELL_CAUTERIZE_HEAL))
                return;

            bool isRank1 = true;
            if (target->HasAura(86949))
                isRank1 = false;

            if ((isRank1 && urand(0, 1) == 1) || !isRank1)
            {
                int32 healAmount = int32(target->CountPctFromMaxHealth(40.0f));

                target->CastCustomSpell(target, MAGE_SPELL_CAUTERIZE_HEAL, NULL, &healAmount, NULL, true);
                absorbAmount = dmgInfo.GetDamage();

                if (target->ToPlayer())
                    target->ToPlayer()->AddSpellCooldown(MAGE_SPELL_CAUTERIZE_HEAL, 0, time(NULL) + 60);
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_cauterize_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_cauterize_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript *GetAuraScript() const 
    {
        return new spell_mage_cauterize_AuraScript();
    }
};

void AddSC_mage_spell_scripts() {
	new spell_mage_cold_snap;
	new spell_mage_frost_warding_trigger();
	new spell_mage_incanters_absorbtion_absorb();
	new spell_mage_incanters_absorbtion_manashield();
	new spell_mage_polymorph_cast_visual; //d
	new spell_mage_blast_wave;
    new spell_mage_summon_water_elemental;
    new spell_mage_cauterize();
}